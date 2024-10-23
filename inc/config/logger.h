#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <fstream>
#include <filesystem>
#include <mutex>
#include <thread>
#include "spdlog/spdlog.h"

static std::vector<std::string> s_log_levels { "debug", "info", "warning", "error", "critical" };

// single ton logger implementation
class Logger {
public:
  Logger(Logger&& ) = delete;
  Logger(const Logger& ) = delete;

  Logger& operator=(Logger&& ) = delete;
  Logger& operator=(const Logger& ) = delete;
  
  static Logger& instance;
private:
  
};

#endif

// Logger db_logger = new Logger("db-logger", ".logs/db/");
// db_logger->info("msg"); // @return: cout?, need to write to debug file.
