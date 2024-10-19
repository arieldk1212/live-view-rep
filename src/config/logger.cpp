#include "../../inc/config/logger.h"

Logger::Logger(const std::string& logger_name, std::string logger_path) {
  m_logger_name = logger_name;
  m_logger_name = logger_path;

  for (int i = 0; i < s_log_levels.size(); i++) {
    std::ofstream file(logger_path + s_log_levels[i] + ".log");

  }
}

void Logger::debug(std::string msg) {

}
