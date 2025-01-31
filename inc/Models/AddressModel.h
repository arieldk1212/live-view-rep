#ifndef ADDRESS_MODEL_H
#define ADDRESS_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class AddressModel : BaseModel {
public:
  explicit AddressModel(std::shared_ptr<DatabaseManager> &Manager);
  ~AddressModel() override;

  pqxx::result Init(const StringUnMap &Fields) override;
  // pqxx::result Add(const StringUnMap &Fields) override;
  // pqxx::result Update(const StringUnMap &Fields) override;
  // pqxx::result Delete(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;
private:
  std::string m_AddressName;
};

#endif
