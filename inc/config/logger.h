#ifndef LOGGER_H
#define LOGGER_H

#include <filesystem>
#include <vector>

#include "spdlog/spdlog.h"

class Logger {
public:    
	
	Logger(const std::string& logger_name, const std::filesystem::path& logger_path);
	virtual ~Logger();
	
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::string m_logger_name;
	std::filesystem::path m_logger_path;
};

class GenericLogger : public Logger {
public:
	GenericLogger();
	~GenericLogger() override;
private:
	std::vector<Logger> m_generic_loggers;
};


#endif