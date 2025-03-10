#ifndef ADDRESS_H
#define ADDRESS_H

#include "Conditions/AddressCondition.h"
#include "Config/DatabaseManager.h"

#include <vector>

/**
 * @brief address api that returns a new instance of this class with the
 * entities (db array) of a specific address, representation of the Address
 * Block.
 */

class Address {
public:
  Address(SharedManager &Manager, std::string IDQuery);
  ~Address() = default;

  [[nodiscard]] const std::string &GetIDQuery() const {
    return m_AddressIDQuery;
  }
  [[nodiscard]] const std::string &GetAddressName() const {
    return m_AddressName;
  }
  [[nodiscard]] const std::string &GetAddressData() const {
    return m_AddressData;
  }

private:
  std::string m_AddressIDQuery;
  std::string m_AddressData;
  std::string m_AddressName;
};

#endif