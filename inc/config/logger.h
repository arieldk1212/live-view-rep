#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class Logger {
public:
  static Logger& GetInstance();
  std::shared_ptr<spdlog::logger> GetLogger(); 

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
private:
  Logger();
  ~Logger();

  std::shared_ptr<spdlog::logger> s_Logger;
};

#define LOG_INFO(...) Logger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LOG_WARNING(...) Logger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define LOG_CRITICAL(...) Logger::GetInstance().GetLogger()->critical(__VA_ARGS__)
#define LOG_TRACE(...) Logger::GetInstance().GetLogger()->trace(__VA_ARGS__)

 #endif
