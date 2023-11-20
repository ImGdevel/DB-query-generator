#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;

class FileManager
{
public:
	vector<string> ReadFileAndSplit(const string& filename);
	vector<string> ReadFileLineByLine(const string& filename);

	void WriteDataToFile(const std::string& filename, const vector<string>& datas);
};

