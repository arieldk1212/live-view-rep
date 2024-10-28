#include "../inc/config/logger.h"

Logger::Logger() {
  s_Logger = spdlog::basic_logger_mt("app", "../../logs/app.log");
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
  s_Logger->set_level(spdlog::level::info);
}

Logger::~Logger() { spdlog::shutdown(); }

Logger& Logger::GetInstance() {
  static Logger instance;
  return instance;
}

std::shared_ptr<spdlog::logger> Logger::GetLogger() { return s_Logger; }
