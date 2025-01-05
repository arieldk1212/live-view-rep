#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

class DatabaseManager;

class DatabaseConnection {
  /*
   * This header file shouldn't be used directly!
   */
public:
  explicit DatabaseConnection(const std::string &ConnectionString);
  ~DatabaseConnection();

  bool IsDatabaseConnected();

private:
  pqxx::connection m_DatabaseConnection;
  // pqxx::work m_DatabaseWorker{m_DatabaseConnection};
  pqxx::nontransaction m_DatabaseNonTransaction{m_DatabaseConnection};

private:
  /**
   * @brief query function that's based on a transaction, via the
   * m_DatabaseWorker, created for update and delete operetions, currently
   * disabled due to no usage.
   * @param Query
   * @return pqxx::result
   */
  // pqxx::result UQuery(const std::string &Query);
  /**
   * @brief query function that's based on a nontransaction, via the
   * m_DatabaseNonTransaction, created for read-only and create operations.
   * @param Query
   * @return pqxx::result
   */
  pqxx::result CrQuery(const std::string &Query);

private:
  friend class DatabaseManager;
};

#endif