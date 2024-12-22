#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Config/Logger.h"

#include <filesystem>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <string>

using Json = nlohmann::json;

/**
 * @todo create a session for dev database, test database, wrap this class into a session class.
 */
class FileSystem {
public:
  explicit FileSystem(const std::filesystem::path &FilePath);
  ~FileSystem() = default;

  Json GetData() const;
  std::string ToString() const;

private:
  std::filesystem::path m_FilePath;
  std::string m_FileName;
  Json m_Data;
};

#endif