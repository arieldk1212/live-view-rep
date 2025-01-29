#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "Config/DatabaseCommands.h"
#include "BaseModel.h"

class LoggerModel : BaseModel {
public:

  explicit LoggerModel(std::shared_ptr<DatabaseManager> &Manager);
  ~LoggerModel() override;

  pqxx::result Add(const StringUnMap &Fields) override;
private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;
private:
  UUID m_LoggerUUID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif
