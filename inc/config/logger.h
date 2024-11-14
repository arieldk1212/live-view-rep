#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <vector>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  static void Init();
  static std::shared_ptr<spdlog::logger> &GetAppLogger();
  static std::shared_ptr<spdlog::logger> &GetSystemLogger();

private:
  static std::shared_ptr<spdlog::logger> s_AppLogger;
  static std::shared_ptr<spdlog::logger> s_SystemLogger;
};

#define APP_INFO(...) Logger::GetAppLogger()->info(__VA_ARGS__)
#define APP_TRACE(...) Logger::GetAppLogger()->trace(__VA_ARGS__)
#define APP_DEBUG(...) Logger::GetAppLogger()->debug(__VA_ARGS__)
#define APP_ERROR(...) Logger::GetAppLogger()->error(__VA_ARGS__)
#define APP_WARNING(...) Logger::GetAppLogger()->warn(__VA_ARGS__)
#define APP_CRITICAL(...) Logger::GetAppLogger()->critical(__VA_ARGS__)

#define SYSTEM_INFO(...) Logger::GetSystemLogger()->info(__VA_ARGS__)
#define SYSTEM_TRACE(...) Logger::GetSystemLogger()->trace(__VA_ARGS__)
#define SYSTEM_DEBUG(...) Logger::GetSystemLogger()->debug(__VA_ARGS__)
#define SYSTEM_ERROR(...) Logger::GetSystemLogger()->error(__VA_ARGS__)
#define SYSTEM_WARNING(...) Logger::GetSystemLogger()->warn(__VA_ARGS__)
#define SYSTEM_CRITICAL(...) Logger::GetSystemLogger()->critical(__VA_ARGS__)

#endif