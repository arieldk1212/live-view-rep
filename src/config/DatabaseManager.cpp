#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager() {
  std::string ConnectionString = "user=arielkriheli password=password "
                                 "host=localhost port=5432 dbname=arielkriheli";
  m_DatabaseConnectionString = std::move(ConnectionString);
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
}

bool DatabaseManager::DatabaseConnectionValidation() {
  return m_DatabaseManager->IsDatabaseConnected();
}

pqxx::result DatabaseManager::Query(const std::string &query) {
  
}