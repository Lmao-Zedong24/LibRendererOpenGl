#include "IResource.h"

std::string IResource::ReadFile(const std::string& p_fileName, const std::string& p_resourcePath)
{
	std::ifstream file;
	file.open(p_resourcePath + p_fileName);

	if (!file.is_open())
		return std::string();

	std::ostringstream sstr;
	sstr << file.rdbuf();

	return sstr.str();
}