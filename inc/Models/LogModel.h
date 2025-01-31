#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

#include <chrono>

class LogModel : BaseModel {
public:
  explicit LogModel(std::shared_ptr<DatabaseManager> &Manager);
  ~LogModel() override;

  pqxx::result Init(const StringUnMap &Fields) override;
  // pqxx::result Add(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  UUID m_LogID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif