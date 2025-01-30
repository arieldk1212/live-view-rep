#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString} {
  APP_INFO("DATABASE CONNECTION CONSTRUCTOR INITIALIZED");
}

DatabaseConnection::~DatabaseConnection() {
  m_DatabaseConnection.close();
  APP_INFO("DATABASE CONNECTION CLOSED");
}

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

pqxx::result DatabaseConnection::CrQuery(const std::string &Query) {
  std::lock_guard<std::mutex> lock(m_DatabaseMutex);
  if (!IsDatabaseConnected()) {
    APP_ERROR("CRQUERY - QUERY ERROR - DATABASE CONNECTION ERROR");
    return {};
  }
  try {
    return m_DatabaseNonTransaction.exec(Query);
  } catch (const std::exception &e) {
    APP_ERROR("CRQUERY - QUERY EXECUTION ERROR - " + std::string(e.what()));
    return {};
  }
}

// pqxx::result DatabaseConnection::UQuery(const std::string &Query) {
//   if (IsDatabaseConnected()) {
//     auto Result = m_DatabaseWorker.exec(Query);
//     m_DatabaseWorker.commit();
//     return Result;
//   }
//   return {};
// }
