#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "../DatabaseModel.h"

class LoggerModel {
public:
  ~LoggerModel();

private:
  UUID m_LoggerUUID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif

