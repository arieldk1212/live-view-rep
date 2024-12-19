#include "../../inc/Config/DatabaseManager.h"
#include "Models/DatabaseModel.h"
#include <memory>

DatabaseManager::DatabaseManager()
    // TODO: replace this ctor into a generic one
    : m_DatabaseConnectionString{
          "user=arielkriheli password=password "
          "host=localhost port=5432 dbname=arielkriheli"} {
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
    Response.append(key).append(" ").append(value).append(" ");
  }
  return std::move(Response);
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
  return std::move(GetModel(ModelName)->ModelSerialization());
}

pqxx::result DatabaseManager::Query(const std::string &query) {
  try {
    auto Response = m_DatabaseManager->Query(query);
    m_DatabaseManager->Commit();
    return std::move(Response);
  } catch (pqxx::sql_error const &error) {
    std::cerr << "Query Error -> " << error.what();
    return {};
  } catch (std::exception const &error) {
    std::cerr << "General Error -> " << error.what();
    return {};
  }
}

pqxx::result DatabaseManager::Create(const std::string &TableName,
                                     const StringMap &TableFields) {
  std::string Template = "create table if not exists " + TableName + "(" +
                         QuerySerialization(TableFields) + ")";
  return Query(Template);
};

/*
 * need to fix the fields on create
 */