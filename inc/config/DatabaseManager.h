#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "../Models/DatabaseModel.h"
#include "Database.h"
#include "Logger.h"

#include <iostream>

/**
 * @class DatabaseManager
 * @brief Manges the database models and operations.
 */
class DatabaseManager {
public:
  /**
   * @brief Constructs the DatabaseManager object, according to the database's
   * connection string.
   */
  DatabaseManager();
  /**
   * @brief Deconstructs the DatabaseManager object, clearing the database
   * models.
   * @todo Probably need to change the way it deconstructs.
   */
  ~DatabaseManager();

  bool DatabaseConnectionValidation();
  std::string QuerySerialization(const StringMap &ModelFields);

  std::shared_ptr<DatabaseModel> GetModel(const std::string &ModelName);
  std::shared_ptr<DatabaseModel> &operator[](const std::string &ModelName);

  pqxx::result AddModel(const std::string &ModelName,
                        const StringMap &ModelFields);
  void AddField(const std::string &ModelName, const std::string &FieldName,
                const std::string &FieldType);
  void SwapAllFields(const std::string &ModelName,
                     const StringMap &ModelFields);
  std::string PrintModel(const std::string &ModelName);

  /**
   * @brief this function in resposible for migrating certain changes for an
   * exsiting table.
   *
   * @param TableName - string, name of the table.
   * @param TableFields - StringMap, new fields of the table.
   * @todo implement and probably add option to delete previous data.
   */
  void MigrateTable(const std::string &TableName, const StringMap &TableFields);

private:
  pqxx::result Query(const std::string &Query);
  pqxx::result Create(const std::string &TableName,
                      const StringMap &TableFields);
  void CreateFields();
  void Read();
  void Update();
  void Delete();

private:
  std::string m_DatabaseConnectionString;
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::vector<std::shared_ptr<DatabaseModel>> m_DatabaseModels;
};

#endif