#include "../inc/config/logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


spdlog::logger Logger::s_application_logger;

void Logger::init() {
  spdlog::sink_ptr log_sink = std::make_shared<spdlog::sinks::stdout_color_sinks>();
}
