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
  /*
  * this function is created for "GET" queries.
  */
  pqxx::result Response;
  Response = m_DatabaseManager->Query(query);
  m_DatabaseManager->Commit();
  return Response;
}

std::string_view DatabaseManager::Execute(const std::string &command) {
  /*
   * this function is created for "PUSH/PUT/PATCH" queries.
   */
  const auto result = m_DatabaseManager->Execute(command);
  m_DatabaseManager->Commit();
  return result;
}