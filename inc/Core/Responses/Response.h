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

#include "Config/Logger.h"

#include <chrono>
#include <pqxx/pqxx>

template <typename ResType> class Response {
public:
  using Clock = std::chrono::high_resolution_clock;
  using DoubleDuration = std::chrono::duration<double>;

public:
  virtual ~Response() = 0;

  virtual const std::string GetResponseQuery() const = 0;
  virtual const size_t GetResponseSize() const = 0;

  virtual DoubleDuration RunBenchmark(std::function<void()> Func) = 0;
  virtual const std::string ResponseType() = 0;
};

class DBResponse : Response<pqxx::result> {
public:
  explicit DBResponse(const pqxx::result &ResponseData);
  explicit DBResponse(pqxx::result &&ResponseData);

  [[nodiscard]] const std::string GetResponseQuery() const override {
    return m_ResponseData.query();
  }
  [[nodiscard]] const size_t GetResponseSize() const override { return m_ResponseSize; }

  DoubleDuration RunBenchmark(std::function<void()> Func) override;
  const std::string ResponseType() override { return "Response: Database"; }

private:
  size_t m_ResponseSize;
  pqxx::result m_ResponseData;
};

/**
 * @brief
 * DBResponse x = Manager->AddModel; -> copy ctor
 * return DBReponse(CreateTable(Args...)); -> ctor
 */

#endif