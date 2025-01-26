#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "../../Config/DatabaseManager.h"
#include "../DatabaseModel.h"

class LoggerModel {
public:
  struct LoggerFields {};

  explicit LoggerModel(const std::shared_ptr<DatabaseManager> &Manager);
  ~LoggerModel();

private:
  UUID m_LoggerUUID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif
