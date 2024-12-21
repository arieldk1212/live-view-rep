#include "../../inc/Config/FileSystem.h"

FileSystem::FileSystem(const std::filesystem::path &FilePath) : m_FilePath{FilePath} {
  std::ifstream file(m_FilePath, std::ios::in | std::ios::binary);
  if (!file.is_open()) {
    SYSTEM_ERROR("Error Opening Config File");
  }
  m_FileDataString = std::string(std::istreambuf_iterator<char>(file),
                                 std::istreambuf_iterator<char>());
}