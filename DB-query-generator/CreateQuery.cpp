#include "CreateQuery.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include <unordered_set>
using namespace std;

CreateQuery::CreateQuery(string _tableName)
    : tableName(_tableName){}

CreateQuery::~CreateQuery() {
    for (auto& attribute : attributes)
    {
        delete attribute;
    }
    attributes.clear();
}

/// <summary>
/// 정수형 데이터 생성 : rangeFirst ~ rangeLast 범위내 데이터 생성
/// </summary>
/// <param name="attributeName"> 속성이름 </param>
/// <param name="rangeFirst"> 시작 범위</param>
/// <param name="rangeLast"> 마지막 범위 </param>
/// <param name="idUnique"> 유니크 여부 </param>
void CreateQuery::AddAttributeNumber(string attributeName, int rangeFirst, int rangeLast, bool idUnique)
{
    if (rangeFirst > rangeLast) { 
        std::cout << attributeName << "의 숫자 범위 지정이 잘못 되었습니다." << std::endl;
    }

    attributes.push_back(new AttributeNumber(attributeName, rangeFirst, rangeLast, idUnique));
}

/// <summary>
/// 문자형 데이터 생성 : values 내 데이터 중 랜덤 생성
/// </summary>
/// <param name="attributeName"> 속성이름 </param>
/// <param name="stringList"> 문자 데이터 집합 </param>
/// <param name="idUnique"> 유니크 여부 </param>
void CreateQuery::AddAttributeString(string attributeName, vector<string> stringList, bool idUnique)
{
    attributes.push_back(new AttributeString(attributeName, stringList, idUnique));
}

/// <summary>
/// 날자형 데이터 생성 : _startYear ~ 현제 시각 중 랜덤 생성
/// </summary>
/// <param name="attributeName"> 속성이름 </param>
/// <param name="startYear"> 시작년도</param>
/// <param name="includeTime"> 시간 표시여부 </param>
/// <param name="idUnique"> 유니크 여부 </param>
void CreateQuery::AddAttributeDate(string attributeName, int startYear, bool includeTime, bool idUnique)
{
    attributes.push_back(new AttributeDate(attributeName, startYear, includeTime, idUnique));
}

string CreateQuery::CreateInsertQuery()
{
    std::ostringstream databaseInsertQuery;
    databaseInsertQuery << "INSERT INTO " << tableName << " (";

    size_t attributesSize = attributes.size();

    for (size_t i = 0; i < attributesSize; i++)
    {
        databaseInsertQuery << attributes[i]->name;
        if (i != (attributesSize - 1))
        {
            databaseInsertQuery << ", ";
        }
    }

    databaseInsertQuery << ") VALUES (";

    for (size_t i = 0; i < attributesSize; ++i)
    {
        if (attributes[i]->isUnique) {
            // Unique한 데이터 생성
            databaseInsertQuery << "'" << attributes[i]->GenerateUniqueValue() << "'";
        }
        else {
            // 랜덤으로 생성
            databaseInsertQuery << "'" << attributes[i]->GenerateRandomValue() << "'";
        }


        if (i != (attributesSize - 1))
        {
            databaseInsertQuery << ", ";
        }
    }

    databaseInsertQuery << ");";

    return databaseInsertQuery.str();
}

vector<string> CreateQuery::CreateDatabaseInsertQueries(int createAmount)
{
    queries.clear();

    for (int i = 0; i < createAmount; i++)
    {
        queries.push_back(CreateInsertQuery());
    }
    CheckDuplicateQueryAndChange();

    return queries;
}

vector<string> CreateQuery::AddDatabaseInsertQueries(int createAmount)
{
    for (int i = 0; i < createAmount; i++)
    {
        queries.push_back(CreateInsertQuery());
    }
    CheckDuplicateQueryAndChange();

    return queries;
}

bool CreateQuery::CheckDuplicateQuery() {
    std::unordered_set<string> uniqueQueries;

    for (const auto& query : queries) {
        if (!uniqueQueries.insert(query).second) {
            return true;
        }
    }

    return false;
}

bool CreateQuery::CheckDuplicateQueryAndChange() {
    std::unordered_set<string> uniqueQueries;

    int index = 0;
    for (const auto& query : queries) {

        if (!uniqueQueries.insert(query).second) {
            for (int i = 0; i < 10 && !uniqueQueries.insert(query).second; i++) {
                queries[index] = CreateInsertQuery();
            }
            if (index == 10) {
                cout << "중복된 쿼리 발견...\n";
                return true;
            }
        }
        index++;
    }

    return false;
}