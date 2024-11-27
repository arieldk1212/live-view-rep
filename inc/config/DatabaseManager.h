#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Database.h"
#include "Logger.h"

// TODO: consider vector of shared_ptrs to avoid errors, consider non-default
// ctor, consider threading.

class DatabaseMethods {
  /*
   * this class is responsible for decleration of General Database Methods.
   */
public:
  virtual ~DatabaseMethods() = 0;
  virtual pqxx::result Query(const std::string &query);
};

class DatabaseManager : public DatabaseMethods {
  /*
   * this class is responsible for handling the user's actions for the Database.
   */
public:
  DatabaseManager();
  ~DatabaseManager() override = default;

  bool DatabaseConnectionValidation();
  pqxx::result Query(const std::string &query) override;

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

#endif