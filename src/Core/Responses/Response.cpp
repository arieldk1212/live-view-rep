#include "../../../inc/Core/Responses/Response.h"

template <typename ResType> Response<ResType>::~Response() {}

DBResponse::DBResponse(pqxx::result &&ResponseData)
    : m_ResponseData(std::move(ResponseData)),
      m_ResponseSize(sizeof(ResponseData)) {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

DBResponse::DoubleDuration DBResponse::RunBenchmark() {
  auto start = Clock::now();

  /* Insert Usage Here */

  auto end = Clock::now();
  auto duration = end - start;
  return duration;
}