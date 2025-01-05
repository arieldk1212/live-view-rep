#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "../Models/DatabaseModel.h"
#include "Database.h"
#include "DatabaseCommands.h"
#include "Logger.h"

#include <iostream>
#include <memory>
#include <mutex>

/**
 * @class DatabaseManager
 * @brief Manges the database models and operations, in front of the db itself.
 */
class DatabaseManager {
public:
  /**
   * @brief Constructs the DatabaseManager object, according to the database's
   * connection string.
   */
  DatabaseManager(const std::string &DatabaseConnectionString);
  /**
   * @brief Deconstructs the DatabaseManager object, clearing the database
   * models.
   */
  ~DatabaseManager();

  bool DatabaseConnectionValidation();
  std::string QuerySerialization(const StringUnMap &ModelFields);

  std::shared_ptr<DatabaseModel> &operator[](const std::string &ModelName);
  std::shared_ptr<DatabaseModel> GetModel(const std::string &ModelName);

  /**
   * @brief creates a new DatabaseModel object, creates a new table in the
   * database with the given parameters.
   * @param ModelName string, Model/Table name.
   * @param ModelFields StringMap, fields of the Model/Table.
   * @return pqxx::result the result of the query.
   */
  pqxx::result AddModel(const std::string &ModelName,
                        const StringUnMap &ModelFields);

  pqxx::result RemoveModel(const std::string &ModelName);
  pqxx::result TruncateModel(const std::string &ModelName);

  pqxx::result GetModelData(const std::string &ModelName);
  pqxx::result GetModelData(const std::string &ModelName,
                            const std::string &FieldName,
                            const std::string &FieldValue);
  std::string GetSerializedModelData(const std::string &ModelName);
  /**
   * @brief add fields to an existing table.
   * @param ModelName string, name of the model/table.
   * @param FieldName string, the field name.
   * @param FieldType string, the field type.
   */
  pqxx::result AddColumn(const std::string &ModelName,
                         const std::string &FieldName,
                         const std::string &FieldType);
  pqxx::result DropColumn(const std::string &ModelName,
                          const std::string &FieldName);
  pqxx::result AlterColumn(const std::string &ModelName,
                           const std::string &FieldName,
                           const std::string &NewFieldType);
  /** @brief not in usage, better to delete the model than change all.
  pqxx::result SwapAllColumns(const std::string &ModelName,
                              const StringUnMap &ModelFields);
  */
  pqxx::result InsertInto(const std::string &ModelName,
                          const StringUnMap &Fields);
  pqxx::result UpdateColumn(const std::string &ModelName,
                            const std::string &FieldName,
                            const std::string &NewFieldValue,
                            const std::string &Condition);
  pqxx::result UpdateColumns(const std::string &ModelName,
                             const StringUnMap &Fields,
                             const std::string &Condition);

private:
  /**
   * @brief private database CRUD related methods, they connect only with the
   * model editor above and in DatabaseModel.
   */
  // pqxx::result MUQuery(const std::string &TableName, const std::string
  // &Query);
  pqxx::result MCrQuery(const std::string &TableName, const std::string &Query);
  pqxx::result CreateTable(const std::string &TableName,
                           const StringUnMap &TableFields);
  pqxx::result GetTableData(const std::string &TableName);
  pqxx::result GetTableData(const std::string &TableName,
                            const std::string &TableFieldName,
                            const std::string &TableFieldValue);
  std::string GetSerializedTableData(const std::string &TableName);
  pqxx::result DeleteTable(const std::string &TableName,
                           DatabaseQueryCommands QueryCommand);

private:
  std::string m_DatabaseConnectionString;
  /**
   * @brief to create the connection pool we need, create a new connection, add,
   * remove, lock.
   */
  // std::shared_ptr<DatabasePoolManager> m_DatabaseManager;
  std::shared_ptr<DatabaseConnection> m_DatabaseManager;
  std::vector<std::shared_ptr<DatabaseModel>> m_DatabaseModels;
};

/**
 * @class DatabaseConnectionPoolManager
 * @brief this class is reponsible for the database connection pool, currently
 * still in development.
 * @todo implement this class, adjust connections accordingly, study about
 * pool's more.
 */
class DatabaseConnectionPoolManager {
public:
  void CreateConnection();
  void AddConnection(std::shared_ptr<DatabaseConnection> Connection);
  void RemoveConnection(std::shared_ptr<DatabaseConnection> Connection);
  std::shared_ptr<DatabaseConnection> LockConnection();

private:
  std::string m_DatabaseConnectionString;
  std::vector<std::unique_ptr<DatabaseConnection>> m_DatabaseConnectionPool;
  std::mutex m_DatabaseConnectionPoolMutex;
};

#endif