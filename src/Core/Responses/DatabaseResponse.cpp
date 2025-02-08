#include "../../../inc/Core/Responses/DatabaseResponse.h"

DBResponse::DBResponse(const pqxx::result &ResponseData)
    : m_ResponseData{ResponseData}, m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

DBResponse::DBResponse(pqxx::result &&ResponseData)
    : m_ResponseData{std::move(ResponseData)},
      m_ResponseSize{sizeof(ResponseData)} {
  APP_INFO("Response Size -> " + std::to_string(m_ResponseSize));
}

DBResponse::DoubleDuration
DBResponse::RunBenchmark(std::function<void()> Func) {
  auto start = Clock::now();
  Func();
  auto end = Clock::now();
  auto duration = end - start;
  return duration;
}