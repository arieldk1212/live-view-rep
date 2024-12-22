#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Config/Logger.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <string>

using StringMap = std::map<std::string, std::string>;

class FileSystem {
public:
  FileSystem(const std::filesystem::path &FilePath);
  ~FileSystem() = default;

private:
  std::filesystem::path m_FilePath;
  std::string m_FileName;
  std::string m_FileDataString;
};

#endif