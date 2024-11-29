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
  virtual ~DatabaseMethods() = default;
  virtual pqxx::result Query(const std::string &query) = 0;
  virtual std::string_view Execute(const std::string &command) = 0;
  virtual std::string_view Execute(const std::string_view &command) = 0;
};

class DatabaseManager{
  /*
   * this class is responsible for handling the user's actions for the Database.
   */
public:
  DatabaseManager();
  ~DatabaseManager() = default;

  bool DatabaseConnectionValidation();
  pqxx::result Query(const std::string &query);
  std::string_view Execute(const std::string &command);
  
private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

#endif