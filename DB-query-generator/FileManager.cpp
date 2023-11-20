#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <fstream>


/// <summary>
/// 폴더 datas에 있는 파일을 공백으로 데이터를 구분하여 데이터를 vector<string> 반환합니다.
/// </summary>
/// <param name="filename">파일 이름</param>
/// <returns>파일 데이터</returns>
std::vector<std::string> FileManager::ReadFileAndSplit(const std::string& filename) {
    std::string file_path = "../datas/" + filename;
    std::vector<std::string> result;

    std::ifstream inputFile(file_path);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
            result.push_back(token);
        }
    }

    return result;
}


/// <summary>
/// 폴더 datas에 있는 파일을 Line 단위로 읽고 데이터를 구분하여 데이터를 vector<string> 반환합니다.
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
std::vector<std::string> FileManager::ReadFileLineByLine(const std::string& filename) {
    std::string file_path = "../datas/" + filename;
    std::vector<std::string> result;

    std::ifstream inputFile(file_path);

    if (!inputFile.is_open()) {
        std::cerr << "에러: 파일을 열 수 없습니다: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        result.push_back(line);
    }

    return result;
}

/// <summary>
/// 데이터를 outputs폴더에 저장합니다.
/// </summary>
/// <param name="filename">저장할 파일 이름</param>
/// <param name="datas">데이터</param>
void FileManager::WriteDataToFile(const string& filename, const vector<string>& datas) {
    string file_path = "../outputs/" + filename;

    std::ofstream outputFile(file_path);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    for (const auto& query : datas) {
        outputFile << query << std::endl;
    }

    std::cout << "Data has been written to the file: " << filename << std::endl;
}