#include "Config/Config.h"

Json Config::ReadFile(const std::filesystem::path &Path) {
  try {
    std::ifstream f(Path);
    if (!f) {
      throw std::ios_base::failure("Unable To Open Config File.");
    }
    auto Data = Json::parse(f);
    return Data;
  } catch (const Json::exception &e) {
    std::cerr << "JSON PARSING ERROR - " << e.what();
    return {};
  } catch (const std::exception &e) {
    std::cerr << "FILE OPENING ERROR - " << e.what();
    return {};
  }
}

std::string Config::DatabaseToString(const std::filesystem::path &Path) {
  auto JsonData = ReadFile(Path);
  std::string Data;
  try {
    Data.append("user=")
        .append(JsonData["DATABASE"]["username"])
        .append(" ")
        .append("password=")
        .append(JsonData["DATABASE"]["password"])
        .append(" ")
        .append("host=")
        .append(JsonData["DATABASE"]["host"])
        .append(" ")
        .append("port=")
        .append(JsonData["DATABASE"]["port"])
        .append(" ")
        .append("dbname=")
        .append(JsonData["DATABASE"]["dbname"]);
    return Data;
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("CONFIG FILE ERROR - DATABASE - " + std::string(e.what()));
    return "";
  }
}

std::string Config::TestDatabaseToString(const std::filesystem::path &Path) {
  auto JsonData = ReadFile(Path);
  std::string Data;
  try {
    Data.append("user=")
        .append(JsonData["TEST_DATABASE"]["username"])
        .append(" ")
        .append("password=")
        .append(JsonData["TEST_DATABASE"]["password"])
        .append(" ")
        .append("host=")
        .append(JsonData["TEST_DATABASE"]["host"])
        .append(" ")
        .append("port=")
        .append(JsonData["TEST_DATABASE"]["port"])
        .append(" ")
        .append("dbname=")
        .append(JsonData["TEST_DATABASE"]["dbname"]);
    return Data;
  } catch (const Json::exception &e) {
    SYSTEM_ERROR("CONFIG FILE ERROR - TEST_DATABASE - " +
                 std::string(e.what()));
    return "";
  }
}

std::string Config::LoggingPathToString(const std::filesystem::path &Path) {
  auto JsonData = ReadFile(Path);
  try {
    return std::string(JsonData["LOGGING"]["path"]);
  } catch (const Json::exception &e) {
    std::cerr << "FILE ERROR AT LOG PATH FUNCTION - " << e.what();
    return "";
  }
}