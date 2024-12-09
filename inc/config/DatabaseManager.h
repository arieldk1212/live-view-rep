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
  std::shared_ptr<DatabaseModel> GetModel(const std::string &ModelName);

  std::shared_ptr<DatabaseModel> &operator[](const std::string &ModelName);

  void AddModel(const std::string &ModelName, const StringMap &ModelFields);
  void AddField(const std::string &ModelName, const std::string &FieldName,
                 const std::string &FieldType);
  void SwapFields(const std::string &ModelName, const StringMap &ModelFields);
  std::string PrintModel(const std::string &ModelName);

  void Create(const std::string &query);
  void Read();
  void Update();
  void Delete();
  pqxx::result Query(const std::string &Query);

private:
  std::string m_DatabaseConnectionString;
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::vector<std::shared_ptr<DatabaseModel>> m_DatabaseModels;
};

#endif