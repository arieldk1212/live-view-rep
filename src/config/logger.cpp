#include "../inc/Config/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_AppLogger;
std::shared_ptr<spdlog::logger> Logger::s_SystemLogger;

void Logger::Init(const std::string &path) {
  std::string p_Path;
  p_Path = (path == "") ? p_Path = "../../backend-logs/" : p_Path = path;

  std::vector<spdlog::sink_ptr> Sinks;

  Sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      p_Path + "app.log", true));
  Sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      p_Path + "sys.log", true));

  Sinks[0]->set_pattern("[%T] [%l] %n: %v");
  Sinks[1]->set_pattern("[%T] [%l] %n: %v");

  s_AppLogger =
      std::make_shared<spdlog::logger>("APP", begin(Sinks), end(Sinks));
  spdlog::register_logger(s_AppLogger);
  s_AppLogger->set_level(spdlog::level::trace);
  s_AppLogger->flush_on(spdlog::level::trace);

  s_SystemLogger =
      std::make_shared<spdlog::logger>("SYSTEM", begin(Sinks), end(Sinks));
  spdlog::register_logger(s_SystemLogger);
  s_SystemLogger->set_level(spdlog::level::trace);
  s_SystemLogger->flush_on(spdlog::level::trace);
}



