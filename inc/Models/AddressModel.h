#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class AddressModel : BaseModel {
  /**
   * @brief in here we need to init a logger for a certain address!
   */
public:
  explicit AddressModel(std::shared_ptr<DatabaseManager> &Manager);
  ~AddressModel() override;

  const std::string GetTableName() const override { return m_TableName; }

  pqxx::result Init() override;
  pqxx::result Add(const StringUnMap &Fields) override;
  pqxx::result Update(const StringUnMap &Fields,
                      const std::string &Condition) override;
  pqxx::result Delete(const std::string &Condition) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;

private:
  std::string m_TableName;
  StringUnMap m_AddressFields = {
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)}};
};

#endif
