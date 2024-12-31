#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager(const std::string &DatabaseConnectionString)
    : m_DatabaseConnectionString(DatabaseConnectionString) {
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
}

DatabaseManager::~DatabaseManager() { m_DatabaseModels.clear(); }

bool DatabaseManager::DatabaseConnectionValidation() {
  return m_DatabaseManager->IsDatabaseConnected();
}

std::string
DatabaseManager::QuerySerialization(const StringUnMap &ModelFields) {
  std::string Response;
  for (const auto &[key, value] : ModelFields) {
    Response.append(key).append(" ").append(value).append(", ");
  }
  if (!ModelFields.empty()) {
    Response.pop_back();
    Response.pop_back();
  }
  return Response;
}

std::shared_ptr<DatabaseModel> &
DatabaseManager::operator[](const std::string &ModelName) {
  for (auto &Model : m_DatabaseModels) {
    if (Model && Model->GetModelName() == ModelName) {
      return Model;
    }
  }
  throw std::out_of_range("Model not found: " + ModelName);
}

std::shared_ptr<DatabaseModel>
DatabaseManager::GetModel(const std::string &ModelName) {
  return (*this)[ModelName];
}

pqxx::result DatabaseManager::AddModel(const std::string &ModelName,
                                       const StringUnMap &ModelFields) {
  m_DatabaseModels.emplace_back(
      std::make_shared<DatabaseModel>(ModelName, ModelFields));
  auto Response = CreateTable(ModelName, ModelFields);
  return Response;
}

void DatabaseManager::AddField(const std::string &ModelName,
                                       const std::string &FieldName,
                                       const std::string &FieldType) {
  GetModel(ModelName)->InsertField(FieldName, FieldType);
}

void DatabaseManager::SwapAllFields(const std::string &ModelName,
                                            const StringUnMap &ModelFields) {
  GetModel(ModelName)->ClearAndInsertFields(ModelFields);
}

pqxx::result DatabaseManager::RemoveModel(const std::string &ModelName) {
  auto it =
      std::find_if(m_DatabaseModels.begin(), m_DatabaseModels.end(),
                   [&ModelName](const std::shared_ptr<DatabaseModel> &Model) {
                     return Model->GetModelName() == ModelName;
                   });
  if (it != m_DatabaseModels.end()) {
    m_DatabaseModels.erase(it);
    return DeleteTable(ModelName, DatabaseQueryCommands::DropDrop);
  }
  throw std::out_of_range("Model not found: " + ModelName);
}

pqxx::result DatabaseManager::TruncateModel(const std::string &ModelName) {
  GetModel(ModelName)->ClearFields();
  return DeleteTable(ModelName, DatabaseQueryCommands::DropTruncate);
}

std::string DatabaseManager::GetModelData(const std::string &ModelName) {
  return GetTable(ModelName);
}

pqxx::result DatabaseManager::Query(const std::string &TableName,
                                    const std::string &query) {
  try {
    auto Response = m_DatabaseManager->Query(query);
    m_DatabaseManager->Commit();
    APP_INFO("SQL TABLE CREATED - " + TableName);
    return Response;
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("QUERY ERROR AT TABLE - " + TableName + " " +
              std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("GENERAL ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::CreateTable(const std::string &TableName,
                                          const StringUnMap &TableFields) {
  std::string query;
  query
      .append(DatabaseCommandToString(
          DatabaseQueryCommands::CreateTableIfNotExists))
      .append(TableName)
      .append("(")
      .append(QuerySerialization(TableFields))
      .append(");");
  return Query(TableName, query);
};

std::string DatabaseManager::GetTable(const std::string &TableName) {
  return GetModel(TableName)->ModelSerialization();
}

pqxx::result DatabaseManager::DeleteTable(const std::string &TableName,
                                          DatabaseQueryCommands QueryCommand) {
  std::string query;
  query.append(DatabaseCommandToString(QueryCommand)).append(TableName);
  return Query(TableName, query);
}