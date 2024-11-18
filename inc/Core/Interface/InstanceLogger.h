#ifndef INSTANCE_LOGGER_H
#define INSTANCE_LOGGER_H

#include <string>

class InstanceLogger {
public:
	virtual ~InstanceLogger();
	virtual void log(std::string &&data) = 0;
};

class AddressLogger final : public InstanceLogger {
public:
	void log(std::string &&data) override;
};

class BusinessLogger final : public InstanceLogger {
public:
	void log(std::string &&data) override;
};

// TODO: street, road, business loggers..

#endif