#include "../../inc/Config/DatabaseManager.h"
#include "Config/Logger.h"

DatabaseManager::DatabaseManager() {
  // TODO: change this to a generic connection string.
  std::string ConnectionString = "user=arielkriheli password=password "
                                 "host=localhost port=5432 dbname=arielkriheli";
  m_DatabaseConnectionString = std::move(ConnectionString);
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
}

DatabaseManager::~DatabaseManager() {
  SYSTEM_CRITICAL("DATABASE CONNECTION DESTROYED");
}

bool DatabaseManager::DatabaseConnectionValidation() {
  return m_DatabaseManager->IsDatabaseConnected();
}

pqxx::result DatabaseManager::Query(const std::string &query) {
  auto Response = m_DatabaseManager->Query(query);
  m_DatabaseManager->Commit();
  return std::move(Response);
}