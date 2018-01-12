#pragma once
#include <string>
#include <vector>
class IOManager
{
public:
	static bool readFileToBuf(std::string filePath, std::vector<char> &buf);
};

