#ifndef DATABASE_H
#define DATABASE_H

#include "Config/Logger.h"

#include <mutex>
#include <pqxx/pqxx>

class DatabaseManager;

class DatabaseConnection {
  /**
   * @warning This header file shouldn't be used directly!
   */
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  DatabaseConnection(const DatabaseConnection &) = delete;
  DatabaseConnection &operator=(const DatabaseConnection &) = delete;

  DatabaseConnection(DatabaseConnection &&) noexcept = delete;
  DatabaseConnection &operator=(DatabaseConnection &&) noexcept = delete;

  bool IsDatabaseConnected();

private:
  friend class DatabaseManager;

private:
  /**
   * @brief query function that's based on a nontransaction, via the
   * m_DatabaseNonTransaction, created for read-only and create operations.
   * @param Query
   * @return pqxx::result
   */
  pqxx::result CrQuery(const std::string &Query);

  /**
   * @brief query function that's based on a transaction, via the
   * m_DatabaseWorker, created for update and delete operetions, currently
   * disabled due to no usage.
   * @param Query
   * @return pqxx::result
   */
  // pqxx::result UQuery(const std::string &Query);

private:
  std::mutex m_DatabaseMutex;
  pqxx::connection m_DatabaseConnection;
  // pqxx::transaction<pqxx::isolation_level::read_committed,
  //                   pqxx::write_policy::read_write>
  //     m_DatabaseTransaction;
  pqxx::nontransaction m_DatabaseNonTransaction;
  // pqxx::work m_DatabaseWorker{m_DatabaseConnection};
};

#endif