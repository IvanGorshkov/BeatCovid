#include "ResourcePath.hpp"

std::string resourcePath() {
  std::string rpath = FILES_PATH;
  rpath += std::string("/");

  return rpath;
}