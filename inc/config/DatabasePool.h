#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include "DatabaseManager.h"

#include <condition_variable>

/**
 * @class DatabaseConnectionPoolManager
 * @brief this class is reponsible for the database connection pool, in dev.
 * @todo add logging into database here, each connection will log its status
 * about himself, user pqxx::lazyconnection, implement cache, fixed number of
 * connections, optimize queries per given time, and monitor!

 * example:
  std::shared_ptr<DatabasePool> Manager = std::make_shared<DatabasePool>(5);
  auto connection_ptr = Manager->get_connection();
  auto limit = Manager->get_pool_limit();
  Manager->disconnect(&connection_ptr);
 */

class DatabasePool {
public:
  DatabasePool(int PoolSize, std::string &&DatabaseConnectionString) noexcept;
  ~DatabasePool();

  inline int GetPoolLimit() const { return m_DatabasePoolSize; }
  inline std::string GetConnectionString() const { return m_DatabaseString; }

  std::shared_ptr<DatabaseManager> &
  GetFreeConnectionByBandwidth(); /* check who's free, gets him. */
  void Recycle(); /* recycle connection, dont disconnect frequently. */

  void SingularConsumption(std::shared_ptr<DatabaseManager> DatabaseManager);
  void Consumptions(); /* status about all connections. */
  void ConnectionsStatus();

  void GetConnection(std::shared_ptr<DatabaseManager> DatabaseManager);
  void ReturnConnection(std::shared_ptr<DatabaseManager> DatabaseManager);
  void Disconnect(std::shared_ptr<DatabaseManager> DatabaseManager);

private:
  std::mutex m_Mutex;
  std::condition_variable m_ConditionVariable;

private:
  int m_DatabasePoolSize;
  std::string m_DatabaseString;
  std::vector<std::shared_ptr<DatabaseManager>> m_DatabasePool;
};

#endif