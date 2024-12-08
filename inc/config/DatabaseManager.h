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

  bool DatabaseConnectionValidation();

  void Create(const std::string &query);
  void Read();
  void Update();
  void Delete();
  pqxx::result Query(const std::string &Query);

  std::string PrintModel(const std::string &ModelName);
  void AddModel(const std::string &ModelName, const StringMap &ModelFields);
  void ChangeModelFields(const std::string &ModelName,
                         const StringMap &ModelFields);

  std::shared_ptr<DatabaseModel> &operator[](const std::string &ModelName);

private:
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::vector<std::shared_ptr<DatabaseModel>> m_DatabaseModels;
  std::string m_DatabaseConnectionString;
};

#endif