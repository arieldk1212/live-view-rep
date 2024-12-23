#include "../../inc/Config/Config.h"

Config::Config(const std::filesystem::path &FilePath)
    : m_FilePath{FilePath} {
  try {
    std::ifstream f(m_FilePath);
    try {
      m_Data = Json::parse(f);
    } catch (const Json::exception &e) {
      SYSTEM_ERROR("File Opening Error - " + e.what());
    }
  } catch (const std::exception &e) {
    SYSTEM_ERROR("File Not Found - " + e.what());
  }
}

const Json Config::GetData() const { return m_Data; }

const std::string Config::DatabaseToString() const {
  std::string Data;
  try {
    Data.append("user=")
        .append(m_Data["DATABASE"]["username"])
        .append(" ")
        .append("password=")
        .append(m_Data["DATABASE"]["password"])
        .append(" ")
        .append("host=")
        .append(m_Data["DATABASE"]["host"])
        .append(" ")
        .append("port=")
        .append(m_Data["DATABASE"]["port"])
        .append(" ")
        .append("dbname=")
        .append(m_Data["DATABASE"]["dbname"]);
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("Config File Error - " + e.what());
  }
  return Data;
}

const std::string Config::TestDatabaseToString() const {
  std::string Data;
  try {
    Data.append("user=")
        .append(m_Data["DATABASE"]["username"])
        .append(" ")
        .append("password=")
        .append(m_Data["DATABASE"]["password"])
        .append(" ")
        .append("host=")
        .append(m_Data["DATABASE"]["host"])
        .append(" ")
        .append("port=")
        .append(m_Data["DATABASE"]["port"])
        .append(" ")
        .append("dbname=")
        .append(m_Data["DATABASE"]["dbname"]);
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("Config File Error - " + e.what());
  }
  return Data;
}

const std::string Config::LoggingPathToString() const {
  return std::string(m_Data["LOGGING"]["PATH"]);
}