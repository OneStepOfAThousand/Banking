#pragma once
#include <string>
#include <vector>
#include <fstream>
class CSVEditor
{
	std::string filePath = "";
	std::ofstream ofstream;
	int size[2] = { 0,0 };
	int cursor[2] = {0,0};

public:
	std::vector<std::string> ReadFile(const std::string& filePath);
	std::vector<std::vector<std::string>>& ReadFileByLine(const std::string& filePath);
	int StartEdit(std::string& filePath);
};

