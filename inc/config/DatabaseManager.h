#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "../Models/DatabaseModel.h"
#include "Database.h"
#include "Logger.h"

#include <iostream>

// TODO: Create vector of shared_ptr's, threading.

class DatabaseManager {
  /*
   * class is responsible for handling the user's actions for the Database.
   */
public:
  DatabaseManager();
  ~DatabaseManager();

  void Create(const std::string &query);
  void Read();
  void Update();
  void Delete();

  bool DatabaseConnectionValidation();
  pqxx::result Query(const std::string &Query);
  void AddModel(const std::string &ModelName, StringMap ModelFields);

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::vector<std::shared_ptr<DatabaseModel>> m_DatabaseModels;
  std::string m_DatabaseConnectionString;
};

#endif