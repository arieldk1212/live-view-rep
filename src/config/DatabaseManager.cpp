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

std::string DatabaseManager::QuerySerialization(const StringMap &ModelFields) {
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

std::shared_ptr<DatabaseModel>
DatabaseManager::GetModel(const std::string &ModelName) {
  return (*this)[ModelName];
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

pqxx::result DatabaseManager::AddModel(const std::string &ModelName,
                                       const StringMap &ModelFields) {
  m_DatabaseModels.emplace_back(
      std::make_shared<DatabaseModel>(ModelName, ModelFields));
  auto Response = Create(ModelName, ModelFields);
  return Response;
}

void DatabaseManager::AddField(const std::string &ModelName,
                               const std::string &FieldName,
                               const std::string &FieldType) {
  GetModel(ModelName)->InsertField(FieldName, FieldType);
}

void DatabaseManager::SwapAllFields(const std::string &ModelName,
                                    const StringMap &ModelFields) {
  GetModel(ModelName)->ClearAndInsertFields(ModelFields);
}

std::string DatabaseManager::PrintModel(const std::string &ModelName) {
  return GetModel(ModelName)->ModelSerialization();
}

pqxx::result DatabaseManager::Query(const std::string &TableName ,const std::string &query) {
  try {
    auto Response = m_DatabaseManager->Query(query);
    m_DatabaseManager->Commit();
    APP_INFO("SQL TABLE CREATED - " + TableName);
    return Response;
  } catch (pqxx::sql_error const &e) {
    APP_ERROR("QUERY ERROR AT TABLE - " + TableName + " " + std::string(e.what()));
    return {};
  } catch (std::exception const &e) {
    APP_ERROR("GENERAL ERROR - " + std::string(e.what()));
    return {};
  }
}

pqxx::result DatabaseManager::Create(const std::string &TableName,
                                     const StringMap &TableFields) {
  std::string query = "create table if not exists " + TableName + "(" +
                      QuerySerialization(TableFields) + ");";
  return Query(TableName, query);
};