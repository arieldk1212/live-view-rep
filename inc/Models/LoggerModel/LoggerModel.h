#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "../../Config/DatabaseManager.h"
#include "Config/DatabaseCommands.h"

class LoggerModel {
public:

  explicit LoggerModel(std::shared_ptr<DatabaseManager> &Manager) {
  }
  ~LoggerModel();

private:
  UUID m_LoggerUUID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

struct LoggerModelGood {
  StringUnMap Fields = {
      {"logger_uuid", DatabaseCommandToString(DatabaseFieldCommands::IntField)},
      {}};
};

#endif
