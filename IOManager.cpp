#include "IOManager.h"
#include <fstream>

bool readFileToBuf(std::string filePath, std::vector<char> &buf)
{
	std::ifstream file(filePath, std::ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}
	//Determine how large the file is.
	//Position file pointer to EOF.
	file.seekg(0, std::ios::end);
	//Return file size from EOF by checking offset between EOF and file[0].
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	//Offset any padding that may be from file headers.
	fileSize -= file.tellg();
	//Resize the vector to create a sufficient pipeline.
	buf.resize(fileSize);
	//Fill the pipeline.
	file.read(&(buf[0]), fileSize);
	//Close the file
	file.close();
	return true;
}
