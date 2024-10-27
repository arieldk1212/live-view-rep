#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <mutex>
#include "spdlog/spdlog.h"

/*
class Logger {
public:
  static void init();

  static spdlog::logger& get_application_logger() { return s_application_logger; }
private:
  static spdlog::logger s_application_logger;
};
*/


class Logger {
public:
  enum class Levels { DEBUG };

private:
  std::string m_LogPath;
private:
  static std::unique_ptr<Logger> s_Logger;
  static std::mutex s_Mutex;
};

 #endif
