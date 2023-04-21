#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <filesystem>

class IResource
{
public:
	virtual void Delete() {}

	// TODO : Update IResource

	//virtual void SetFilePath();
	//virtual void GetFilePath();
	//virtual void ReadFile(const std::string& p_fileName, const std::string& p_resourcePath);

protected:
	std::string WriteFileInString(const std::string& p_fileName, const std::string& p_resourcePath = "");
};

