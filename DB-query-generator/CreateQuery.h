#pragma once
#include "Attribute.h"
#include <string>
#include <vector>
using std::vector;
using std::string;


class CreateQuery
{
public:
    CreateQuery(string tableName);
    ~CreateQuery();
    vector<string> CreateDatabaseInsertQueries(int createAmount);
    vector<string> AddDatabaseInsertQueries(int createAmount);

    void AddAttributeNumber(string attributeName, int rangeFirst, int rangeLast, bool idUnique = false);
    void AddAttributeString(string attributeName, vector<string> stringList, bool idUnique = false);
    void AddAttributeDate(string attributeName, int startYear, bool includeTime, bool idUnique = false);
    bool CheckDuplicateQuery();
    bool CheckDuplicateQueryAndChange();

private:
    CreateQuery();
    string CreateInsertQuery();

    string tableName;
    vector<Attribute*> attributes;
    vector<string> queries;
};