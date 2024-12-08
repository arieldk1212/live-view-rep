#include "../../inc/Config/DatabaseManager.h"
#include "Models/DatabaseModel.h"
#include <memory>

DatabaseManager::DatabaseManager()
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

std::shared_ptr<DatabaseModel> &
DatabaseManager::operator[](const std::string &ModelName) {
  for (auto &Model : m_DatabaseModels) {
    if (Model && Model->GetModelName() == ModelName) {
      return Model;
    }
  }
}

std::string DatabaseManager::PrintModel(const std::string &ModelName) {
  return std::move((*this)[ModelName]->ModelSerialization());
}

void DatabaseManager::AddModel(const std::string &ModelName,
                               const StringMap &ModelFields) {
  m_DatabaseModels.emplace_back(
      std::make_shared<DatabaseModel>(ModelName, ModelFields));
}

void DatabaseManager::ChangeModelFields(const std::string &ModelName,
                                        const StringMap &ModelFields) {
  (*this)[ModelName]->ClearAndInsertFields(ModelFields);
}