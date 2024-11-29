#include "../../inc/Config/DatabaseManager.h"

DatabaseManager::DatabaseManager() {
  // SYSTEM_TRACE("DATABASE CONNECTION ESTABLISHED"); // INFO: database tests not working when this enabled..
  // TODO: change this to a generic connection string.
  std::string ConnectionString = "user=arielkriheli password=password "
                                 "host=localhost port=5432 dbname=arielkriheli";
  m_DatabaseConnectionString = std::move(ConnectionString);
  m_DatabaseManager =
      std::make_shared<DatabaseConnection>(m_DatabaseConnectionString);
}

DatabaseManager::~DatabaseManager() {
  // SYSTEM_TRACE("DATABASE CONNECTION DESTROYED"); // INFO: also this..
}

bool DatabaseManager::DatabaseConnectionValidation() {
  return m_DatabaseManager->IsDatabaseConnected();
}

pqxx::result DatabaseManager::Query(const std::string &query) {
  auto Response = m_DatabaseManager->Query(query);
  m_DatabaseManager->Commit();
  return std::move(Response);
}