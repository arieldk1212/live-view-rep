#ifndef ADDRESS_LOGGER_H
#define ADDRESS_LOGGER_H

#include <string>

class Logger {
  virtual void log(std::string &&data) = 0;
};

class AddressLogger : public Logger {
public:
  void log(std::string &&data) override {
    // TODO: insert logic here.
  }
};

#endif