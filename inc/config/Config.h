#ifndef CONFIG_H
#define CONFIG_H

#include "Config/Logger.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <string>

using Json = nlohmann::json;

/**
 * @todo create a session for dev database, test database, wrap this class into
 * a session class, adjust the filesystem for displaying the data - api.
 */
class Config {
public:
  explicit Config(const std::filesystem::path &FilePath);
  ~Config() = default;

  /**
   * @brief returns a read-only of the config.json data
   * @return const Json Object
   */
  const Json GetData() const;

  /**
   * @brief returns a read-only of the DatabaseConnectionString from config.json
   * @return const std::string
   */
  const std::string DatabaseToString() const;

  /**
   * @brief returns a read-only of the TestDatabaseConnectionString from config.json
   * @return const std::string
   */
  const std::string TestDatabaseToString() const;

  const std::string LoggingPathToString() const;

private:
  std::filesystem::path m_FilePath;
  Json m_Data;
};

#endif