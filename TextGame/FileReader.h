#pragma once
#include <string>
#include <fstream>

static class FileReader
{
public:
	FileReader();

	bool readFile(const std::string& file, std::string& storeString);  //Returns false if file fails to open
	bool readFileToLower(const std::string& file, std::string& storeString);
	bool readFileToUpper(const std::string& file, std::string& storeString);

private:
	std::fstream _fileStream;

} fileReader;

