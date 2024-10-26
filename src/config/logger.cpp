#include "../inc/config/logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


spdlog::logger Logger::s_application_logger;

void Logger::init() {
  std::vector<spdlog::sink_ptr> log_sinks;
  log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sinks>());
  log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink>("Test.log", true));
  
  s_application_logger = std::make_shared<spdlog::logger>("APP", begin(log_sinks), end(log_sinks));
  spdlog::register_logger(s_application_logger);


}
