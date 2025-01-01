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
   * @todo Probably need to change the way it deconstructs, maybe when model
   * deleted run delete in sql.
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
  /**
   * @brief adds fields to an existing table.
   * @param ModelName string, name of the model/table.
   * @param FieldName string, the field name.
   * @param FieldType string, the field type.
   */
  void AddField(const std::string &ModelName, const std::string &FieldName,
                const std::string &FieldType);
  void SwapAllFields(const std::string &ModelName,
                     const StringUnMap &ModelFields);

  pqxx::result RemoveModel(const std::string &ModelName);
  pqxx::result TruncateModel(const std::string &ModelName);

  pqxx::result GetModelData(const std::string &ModelName);
  std::string GetSerializedModelData(const std::string &ModelName);

  /**
   * @brief this function in resposible for migrating certain changes for an
   * exsiting table, compares the changes in a given DatabaseModel, migrates the
   * changes to the database.
   * @param TableName - string, name of the table.
   * @param TableFields - StringMap, new fields of the table.
   * @todo implement this, after client editing changes in DatabaseModel, should
   * call this function.
   */
  pqxx::result Migrate(const std::string &TableName,
                       const StringUnMap &TableFields);

private:
  /**
   * @brief private database CRUD related methods, they connect only with the
   * model editor above and in DatabaseModel.
   */
  pqxx::result Query(const std::string &TableName, const std::string &Query);
  pqxx::result CreateTable(const std::string &TableName,
                           const StringUnMap &TableFields);
  pqxx::result GetTableData(const std::string &TableName);
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