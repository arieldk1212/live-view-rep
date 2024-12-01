#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Database.h"
#include "Logger.h"

// TODO: Create vector of shared_ptr's, threading.

class DatabaseManager {
  /*
   * this class is responsible for handling the user's actions for the Database.
   */
public:
  DatabaseManager();
  ~DatabaseManager() = default;

  bool DatabaseConnectionValidation();
  pqxx::result Query(const std::string &query);

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

#endif