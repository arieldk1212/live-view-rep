#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "Config/DatabaseManager.h"
#include "Model.h"

class LogModel final {
public:
  LogModel();
  ~LogModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(SharedManager &Manager, const StringUnMap &Fields);

private:
  std::string m_TableName;
};

#endif