#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <fstream>
#include <filesystem>
#include "spdlog/spdlog.h"

static std::vector<std::string> s_log_levels { "debug", "info", "warning", "error", "critical" };

class Logger {
public:    

	Logger() = delete;
	Logger(const std::string& logger_name, std::string logger_path);
	~Logger() = default;
	
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void debug(std::string msg);

private:
	std::string m_logger_name;
	std::filesystem::path m_logger_path;
	std::vector<std::string> m_logger_files; // INFO: will store the files path.
};

#endif

// Logger db_logger = new Logger("db-logger", ".logs/db/");
// db_logger->info("msg"); // @return: cout?, need to write to debug file.