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
protected:
	std::string ReadFile(const std::string& p_fileName, const std::string& p_resourcePath = "");
};

