#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "../Core/Address/Address.h"
#include "Model.h"

class AddressModel final {
  /**
   * @brief in here we need to init a logger for a certain address!
   * separate here to entites and make a list inside the model of the data? if
   * yes, how do we extract it?
   */
public:
  AddressModel();
  ~AddressModel();

  [[nodiscard]] const std::string &GetTableName() const { return m_TableName; }

  pqxx::result Add(SharedManager &Manager, StringUnMap Fields);

  /**
   * @brief Get the Address ID.
   * @tparam Args
   * @param Manager
   * @param args (addressname, addressnumber)
   * @return std::string
   */
  template <typename... Args>
  [[nodiscard]] std::string GetAddressID(SharedManager &Manager,
                                         Args &&...args) {
    auto Result =
        Manager->GetModelDataArgs(m_TableName, "addressname", "addressnumber",
                                  std::forward<Args>(args)...);
    return Result[0]["addressid"].template as<std::string>();
  }

  template <typename T>
  pqxx::result Update(SharedManager &Manager, const StringUnMap &Fields,
                      const std::string &Condition, T &&arg) {
    pqxx::params params;
    if (Fields.size() == 1) {
      auto field = Fields.begin();
      params.append(field->second);
      params.append(std::forward<T>(arg));
      return Manager->UpdateColumn(m_TableName, field->first, Condition,
                                   params);
    }
    for (const auto &[key, value] : Fields) {
      params.append(value);
    }
    params.append(std::forward<T>(arg));
    return Manager->UpdateColumns(m_TableName, Fields, Condition, params);
  }

  template <typename T>
  pqxx::result Delete(SharedManager &Manager, const std::string &Condition,
                      T &&arg) {
    pqxx::params params;
    params.append(std::forward<T>(arg));
    return Manager->DeleteRecord(m_TableName, Condition, params);
  }

  [[nodiscard]] Address GetAddressData(SharedManager &Manager, std::string ID);

private:
  std::string m_TableName;
};

#endif