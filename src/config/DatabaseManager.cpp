#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager() {
  // TODO: change this to a generic connection string.
  m_DatabaseConnectionString = "user=arielkriheli password=password "
                               "host=localhost port=5432 dbname=arielkriheli";
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