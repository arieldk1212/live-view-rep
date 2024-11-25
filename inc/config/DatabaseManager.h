#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Database.h"
#include "Logger.h"

#include <memory>

class DatabaseManager {
public:
  DatabaseManager();
  ~DatabaseManager();

  void CreateTable(const std::string &TableName);
  void WriteToTable(const std::string &TableName, const std::string &Data);
  bool TableExists(const std::string &TableName);
  void DeleteTable(const std::string &TabelName);

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

#endif