#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "Database.h"
#include "Logger.h"

// TODO: consider vector of shared_ptrs to avoid errors, consider non-default
// ctor, consider threading.
// TODO: add generic methods like insert, delete, update, get.

class DatabaseManager {
  /*
   * this class is responsible for handling the user's actions for the Database.
   */
public:
  DatabaseManager();
  ~DatabaseManager();

  bool DatabaseConnectionValidation();
  pqxx::result Query(const std::string &query);

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::string m_DatabaseConnectionString;
};

// try {
//   stuff
// }
// catch (pqxx::sql_error const &e) {
//   std::cerr << "SQL error: " << e.what();
//   std::cerr << "Query was: " << e.query();
//   return 2;
// }
// catch (std::exception const &e) {
//   std::cerr << "Error: " << e.what() << std::endl;
//   return 1;
// }

#endif