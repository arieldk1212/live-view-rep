#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "DB.h"
#include "Logger.h"

#include <memory>

// typedef std::shared_ptr<pqxx::connection> DBPtr;

class DBManager {
public:
  DBManager();
  ~DBManager();

  void CreateTable(const std::string &TableName);
  void WriteToTable(const std::string &TableName, const std::string &Data);
  bool TableExists(const std::string &TableName);
  void DeleteTable(const std::string &TabelName);

private:
  std::shared_ptr<DBConnection> m_DB;
  std::string m_DBConnectionString;
};

#endif