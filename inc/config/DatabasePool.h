#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include "DatabaseManager.h"

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
  struct Connection {
    uint64_t m_ConnectionBandwidth;
    size_t m_ConnectionHits; /* increases to find anomaly if one connection gets
                                overused.*/
    std::unique_ptr<DatabaseManager> m_Connection;
  };

public:
  DatabasePool(int PoolSize,
               std::string_view DatabaseConnectionString) noexcept;
  ~DatabasePool();

  inline int GetPoolLimit() const { return m_DatabasePoolSize; }

  std::unique_ptr<Connection> &
  GetFreeConnectionByBandwidth(); /* check who's free, gets him. */
  void Recycle();

  void SingularConsumption(std::unique_ptr<Connection> Connection);
  void Consumptions();
  void ConnectionsStatus();
  void GetConnection(std::unique_ptr<Connection> Connection);
  void Disconnect(std::unique_ptr<Connection> Connection);

private:
  int m_DatabasePoolSize;
  std::mutex m_DatabasePoolMutex;
  std::string m_DatabaseConnectionString;
  std::vector<std::shared_ptr<DatabaseManager>> m_DatabasePool;
};

#endif