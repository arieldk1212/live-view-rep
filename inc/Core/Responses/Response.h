#ifndef RESPONSE_H
#define RESPONSE_H

// Entity
// TODO: add logic for the data separation from the full address to entity
// block. INFO: when i get the address from the Address Class, it will be passed
// down to Entity and the logic of the address separation to entities will be
// dealt here, meaning i probably want to change the Entity Ctor to the address
// itself, and the separate to Entities ( Data Structures ). INFO: the address
// class will inherit from entity due to the need use of the private entity
// members and their functionality.

/**
 * @brief valid can try and figure out a generic form of responses from
 * different application sections.
 */

#include "Config/Logger.h"

#include <chrono>
#include <pqxx/pqxx>

template <typename ResType> class Response {
public:
  using Clock = std::chrono::high_resolution_clock;
  using DoubleDuration = std::chrono::duration<double>;

public:
  virtual ~Response() = 0;

  virtual void Query() = 0;
  virtual void ToString() = 0;

  virtual DoubleDuration RunBenchmark() = 0;
  virtual const std::string ResponseType() = 0; /* e.g database response.. */
};

class DBResponse : Response<pqxx::result> {
public:
  DBResponse(pqxx::result &&ResponseData);

  /**
   * @brief depends on how the usage will be, operator= will be good.
   */
  DBResponse &operator=(std::function<pqxx::result> Func);

  DoubleDuration RunBenchmark() override;
  const std::string ResponseType() override { return "Response: Database"; }

private:
  size_t m_ResponseSize;
  pqxx::result m_ResponseData;
};

/**
 * @brief
 * DBResponse x = Manager->AddModel; -> operator=
 * return DBReponse(CreateTable(Args...)); -> copy ctor
 */

#endif