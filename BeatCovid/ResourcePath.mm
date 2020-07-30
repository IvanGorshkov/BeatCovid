#include <direct.h>
#include "ResourcePath.hpp"

std::string resourcePath() {
	char currentWorkDir[FILENAME_MAX];
	_getcwd(currentWorkDir, sizeof(currentWorkDir));

	std::string rpath(currentWorkDir);
	rpath += std::string("/");

	return rpath;
}