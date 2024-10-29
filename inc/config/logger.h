#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class Logger {
public:
  static void Init();

  static std::shared_ptr<spdlog::logger>& GetLogger();

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

#define APP_INFO(...)     Logger::GetLogger()->info(__VA_ARGS__)
#define APP_TRACE(...)    Logger::GetLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...)    Logger::GetLogger()->debug(__VA_ARGS__)
#define APP_WARNING(...)  Logger::GetLogger()->warn(__VA_ARGS__)
#define APP_CRITICAL(...) Logger::GetLogger()->critical(__VA_ARGS__)

#endif