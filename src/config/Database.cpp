#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString} {}

DatabaseConnection::~DatabaseConnection() {
  // m_DatabaseWorker.abort();
  m_DatabaseConnection.close();
}

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

// pqxx::result DatabaseConnection::UQuery(const std::string &Query) {
//   if (IsDatabaseConnected()) {
//     auto Result = m_DatabaseWorker.exec(Query);
//     m_DatabaseWorker.commit();
//     return Result;
//   }
//   return {};
// }

pqxx::result DatabaseConnection::CrQuery(const std::string &Query) {
  if (IsDatabaseConnected()) {
    return m_DatabaseNonTransaction.exec(Query);
  }
  return {};
}