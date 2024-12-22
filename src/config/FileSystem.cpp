#include "../../inc/Config/FileSystem.h"

FileSystem::FileSystem(const std::filesystem::path &FilePath)
    : m_FilePath{FilePath} {
  std::ifstream f(m_FilePath);
  m_Data = Json::parse(f);
}

Json FileSystem::GetData() const { return m_Data; }

std::string FileSystem::ToString() const {
  std::string Data;
  Data.append(m_Data["DATABASE"]["username"])
      .append(" ")
      .append(m_Data["DATABASE"]["password"])
      .append(" ")
      .append(m_Data["DATABASE"]["host"])
      .append(" ")
      .append(m_Data["DATABASE"]["port"])
      .append(" ")
      .append(m_Data["DATABASE"]["dbname"]);
  return Data;
}