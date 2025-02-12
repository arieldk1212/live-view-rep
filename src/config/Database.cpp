#include "../../inc/Config/Database.h"

DatabaseConnection::DatabaseConnection(const std::string &ConnectionString)
    : m_DatabaseConnection{ConnectionString},
      m_DatabaseNonTransaction(m_DatabaseConnection) {
  APP_INFO("DATABASE CONNECTION CREATED");
}

DatabaseConnection::~DatabaseConnection() {
  m_DatabaseConnection.close();
  APP_CRITICAL("DATABASE CONNECTION CLOSED");
}

bool DatabaseConnection::IsDatabaseConnected() {
  return m_DatabaseConnection.is_open();
}

pqxx::result DatabaseConnection::CrQuery(const std::string &Query) {
  /**
   * @todo need to change this to a concurrent environment. meaning no mutex,
   * init another connection or execute multiple times, test it, check pqxx
   docs.
   * allow multi threaded runs, connection pool??
   * FROM THE PQXX DOCS:
   * Treat a connection, together with any and all objects related to it, as a
   "world" of its own. You should generally make sure that the same "world" is
   never accessed by another thread while you're doing anything non-const in
   there.
   * Not within the same connection. Even if you use nested transactions (see
   the subtransaction class), a connection is always dealing with just one
   transaction at a time. Of course you can create a new transaction on the same
   connection once the previous one has completed. If you want to have multiple
   concurrent transactions, let them work on different connections.
   */
  if (!IsDatabaseConnected()) {
    APP_ERROR("CRQUERY - QUERY ERROR - DATABASE CONNECTION ERROR");
    return {};
  }
  try {
    std::lock_guard<std::mutex> lock(m_DatabaseMutex);
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