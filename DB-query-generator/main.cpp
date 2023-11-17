#include "CreateQuery.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

int main() {
    FileManager fileManager;
    CreateQuery creator = CreateQuery("table_Name");
    
    /* Attribute 설정 */
    creator.AddAttributeNumber("id", 10000, 69999, true);
    creator.AddAttributeString("name", fileManager.ReadFileAndSplit("text.txt"), true);
    creator.AddAttributeDate("day", 1980, false);
    
    /* 쿼리 생성 */
    int createAmount = 100; //생성 개수
    vector<string> datas = creator.CreateDatabaseInsertQueries(createAmount);

    
    for (const auto& query : datas) {
        std::cout << query << std::endl;
    }
    
    /* txt파일로 */
    fileManager.WriteDataToFile("output.txt", datas);

    return 0;
}
