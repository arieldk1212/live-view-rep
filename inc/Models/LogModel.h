#ifndef LOG_MODEL_H
#define LOG_MODEL_H

#include "Config/DatabaseManager.h"
#include "Model.h"

class LogModel {
public:
  LogModel();
  virtual ~LogModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(SharedManager &Manager, const StringUnMap &Fields);

private:
  std::string m_TableName;
};

class AddressLog : public LogModel {
public:
  AddressLog();
  ~AddressLog();

private:
  std::string m_TableName;
};

#endif