#include "../inc/Config/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_AppLogger;
std::shared_ptr<spdlog::logger> Logger::s_SystemLogger;

void Logger::Init() {
  // INFO: App Logger Init
  spdlog::sink_ptr app_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("../logs/app.log",
                                                          true);
  app_sink->set_pattern("[%T] [%l] %n: %v");
  s_AppLogger = std::make_shared<spdlog::logger>("APP", app_sink);
  spdlog::register_logger(s_AppLogger);
  s_AppLogger->set_level(spdlog::level::trace);
  s_AppLogger->flush_on(spdlog::level::trace);

  // INFO: System Logger Init
  spdlog::sink_ptr system_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("../logs/sys.log",
                                                          true);
  system_sink->set_pattern("[%T] [%l] %n: %v");
  s_SystemLogger = std::make_shared<spdlog::logger>("SYSTEM", system_sink);
  spdlog::register_logger(s_SystemLogger);
  s_SystemLogger->set_level(spdlog::level::trace);
  s_SystemLogger->flush_on(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> &Logger::GetAppLogger() { return s_AppLogger; }
std::shared_ptr<spdlog::logger> &Logger::GetSystemLogger() {
  return s_SystemLogger;
}