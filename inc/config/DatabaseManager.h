#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Database.h"
#include "Logger.h"

#include <memory>

class DatabaseManager {
public:
  DatabaseManager();
  ~DatabaseManager() = default;

  bool ValidateDatabase();

 private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

#endif