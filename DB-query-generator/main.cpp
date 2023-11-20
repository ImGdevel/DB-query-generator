#include "CreateQuery.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

int main() {
    FileManager fileManager;
    CreateQuery creator = CreateQuery("직원");
    
    /* Attribute 설정 */
    creator.AddAttributeString("직원번호", fileManager.ReadFileAndSplit("sample_직원_직원번호.txt"), true);
    creator.AddAttributeString("직원명", fileManager.ReadFileAndSplit("sample_직원_이름.txt"), true);
    creator.AddAttributeString("주민등록번호", fileManager.ReadFileAndSplit("sample_직원_주민등록번호.txt"), true);
    creator.AddAttributeString("최종학력", fileManager.ReadFileLineByLine("sample_직원_최종학력.txt"));
    creator.AddAttributeString("직위", fileManager.ReadFileAndSplit("sample_직원_직위.txt"));
    creator.AddAttributeNumber("소속부서", 101, 104);
    creator.AddAttributeNumber("정보 권한 등급", 1, 1);

    /* 쿼리 생성 */
    int createAmount = 70; //생성 개수
    vector<string> datas = creator.CreateDatabaseInsertQueries(createAmount);

    
    for (const auto& query : datas) {
        std::cout << query << std::endl;
    }
    
    /* txt파일로 */
    fileManager.WriteDataToFile("개발자.txt", datas);

    return 0;
}
