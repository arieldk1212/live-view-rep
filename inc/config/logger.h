#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <fstream>
#include <memory>
#include <filesystem>
#include <mutex>
#include <thread>
#include "spdlog/spdlog.h"

class Logger {
public:
  static void init();

  static spdlog::logger& get_application_logger() { return s_application_logger; }
private:
  static spdlog::logger s_application_logger;
};

 #endif

// Logger db_logger = new Logger("db-logger", ".logs/db/");
// db_logger->info("msg"); // @return: cout?, need to write to debug file.
