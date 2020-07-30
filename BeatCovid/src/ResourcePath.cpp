#include <direct.h>
#include "ResourcePath.hpp"

std::string resourcePath(void) {
	char current_work_dir[FILENAME_MAX];
	_getcwd(current_work_dir, sizeof(current_work_dir));

	std::string rpath(current_work_dir);
	rpath += std::string("/");

	return rpath;
}