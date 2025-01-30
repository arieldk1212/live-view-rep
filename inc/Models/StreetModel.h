#ifndef STREET_MODEL_H
#define STREET_MODEL_H

#include "BaseModel.h"
#include "Config/DatabaseCommands.h"

class StreetModel : BaseModel {
public:
  explicit StreetModel(std::shared_ptr<DatabaseManager> &Manager);
  ~StreetModel() override;

  pqxx::result Add(const StringUnMap &Fields) override;
  pqxx::result Update(const StringUnMap &Fields) override;
  pqxx::result Delete(const StringUnMap &Fields) override;

private:
  std::shared_ptr<DatabaseManager> m_DatabaseManager;
private:
  std::string m_StreetName;
};

#endif
