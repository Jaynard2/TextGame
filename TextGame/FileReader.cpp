#include "FileReader.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

FileReader::FileReader() : _fileStream()
{
}

bool FileReader::readFile(const std::string& file, std::string& storeString)
{
	_fileStream.open(file);

	if (_fileStream.fail())
	{
		perror(file.c_str());
		_fileStream.close();
		return false;
	}

	std::string tmp;
	while (std::getline(_fileStream, tmp))
	{
		tmp += "\n";
		storeString.append(tmp);
	}

	_fileStream.close();
	return true;
}

bool FileReader::readFileToLower(const std::string& file, std::string& storeString)
{
	if (readFile(file, storeString))
	{
		std::transform(storeString.begin(), storeString.end(), storeString.begin(), ::tolower);
		return true;
	}

	return false;
}

bool FileReader::readFileToUpper(const std::string& file, std::string& storeString)
{
	if (readFile(file, storeString))
	{
		std::transform(storeString.begin(), storeString.end(), storeString.begin(), ::toupper);
		return true;
	}

	return false;
}
