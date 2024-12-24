#include "../../inc/Config/Config.h"

Config::Config(const std::filesystem::path &FilePath)
    : m_FilePath{FilePath} {
  try {
    std::ifstream f(m_FilePath);
    try {
      m_Data = Json::parse(f);
    } catch (const Json::exception &e) {
      SYSTEM_ERROR("FILE ERROR - PARSE - " + e.what());
    }
  } catch (const std::exception &e) {
    SYSTEM_ERROR("FILE PATH ERROR - STREAM - " + e.what());
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
    SYSTEM_ERROR("CONFIG FILE ERROR - DATABASE - " + e.what());
  }
  return Data;
}

const std::string Config::TestDatabaseToString() const {
  std::string Data;
  try {
    Data.append("user=")
        .append(m_Data["TEST_DATABASE"]["username"])
        .append(" ")
        .append("password=")
        .append(m_Data["TEST_DATABASE"]["password"])
        .append(" ")
        .append("host=")
        .append(m_Data["TEST_DATABASE"]["host"])
        .append(" ")
        .append("port=")
        .append(m_Data["TEST_DATABASE"]["port"])
        .append(" ")
        .append("dbname=")
        .append(m_Data["TEST_DATABASE"]["dbname"]);
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("CONFIG FILE ERROR - TEST_DATABASE - " + e.what());
  }
  return Data;
}

const std::string Config::LoggingPathToString() const {
  try {
    return std::string(m_Data["LOGGING"]["PATH"]);
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("CONFIG FILE ERROR - LOGGING - " + e.what());
  }
}
