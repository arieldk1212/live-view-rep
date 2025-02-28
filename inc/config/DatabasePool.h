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
  Shared<DatabasePool> Manager = std::make_shared<DatabasePool>(5);
  auto connection_ptr = Manager->get_connection();
  auto limit = Manager->get_pool_limit();
  Manager->disconnect(&connection_ptr);
 * alternative example:
  Shared<DatabasePool> Manager = std::make_shared<DatabasePool>(5);
  auto conn = Manager->GetConnection();
  ...
  ...
  ...
  Manager->shutdown();
 */

class DatabasePool {
public:
  template <typename T> using Shared = std::shared_ptr<T>;
  using SharedManager = Shared<DatabaseManager>;

public:
  DatabasePool(int PoolSize, std::string &&DatabaseConnectionString);
  ~DatabasePool();

  void Shutdown();

  inline int GetPoolLimit() const { return m_DatabasePoolSize; }
  inline std::string GetConnectionString() const { return m_DatabaseString; }

  SharedManager &
  GetFreeConnectionByBandwidth(); /* check who's free, gets him. */
  void Recycle(); /* recycle connection, dont disconnect frequently. */

  void SingularConsumption(SharedManager DatabaseManager);
  void Consumptions();      /* status about all connections. */
  void ConnectionsStatus(); /* by connection strings? */

  SharedManager &GetConnection();
  void ReturnConnection(SharedManager DatabaseManager);
  void Disconnect(SharedManager DatabaseManager);

private:
  std::mutex m_Mutex;
  std::condition_variable m_ConditionVariable;

private:
  int m_DatabasePoolSize;
  std::string m_DatabaseString;
  std::vector<SharedManager> m_DatabasePool;
};

#endif