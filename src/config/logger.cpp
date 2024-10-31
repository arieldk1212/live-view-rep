#include <spdlog/sinks/basic_file_sink.h>

#include "../inc/Config/Logger.h"

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Init() {
  spdlog::sink_ptr sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "../logs/app.log", true);
  sink->set_pattern("[%T] [%l] %n: %v");

  s_Logger = std::make_shared<spdlog::logger>("APP", sink);
  spdlog::register_logger(s_Logger);
  s_Logger->set_level(spdlog::level::trace);
  s_Logger->flush_on(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> &Logger::GetLogger() { return s_Logger; }