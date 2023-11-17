#include "FileManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

vector<string> FileManager::ReadFileAndSplit(const string& filename) {
    string file_path = "../datas/" + filename;
    vector<string> result;

    std::ifstream inputFile(file_path);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file: " << filename << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string token;

        while (std::getline(iss, token, ' ')) {
            result.push_back(token);
        }
    }

    return result;
}

void FileManager::WriteDataToFile(const string& filename, const vector<string>& datas) {
    string file_path = "../output/" + filename;

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