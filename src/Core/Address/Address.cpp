#include "../../../inc/Core/Address/Address.h"

Address::Address(SharedManager &Manager, std::string IDQuery)
    : m_AddressIDQuery(std::move(IDQuery)) {
  auto Result = Manager->GetModelData("Address", "addressid", m_AddressIDQuery);
  m_AddressIDQuery = Result[0]["addressid"].as<std::string>();
  m_AddressName = Result[0]["addressname"].as<std::string>();
  m_AddressData = Result[0]["addressdata"].as<std::string>();
}