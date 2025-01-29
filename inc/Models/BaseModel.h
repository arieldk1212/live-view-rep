#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include "Config/Config.h"
#include "Config/DatabaseManager.h"
#include <pqxx/pqxx>

class BaseModel {
  virtual ~BaseModel() = default;
  virtual pqxx::result Add(const StringUnMap &Fields) = 0;
  virtual pqxx::result Update(const StringUnMap &Fields) = 0;
  virtual pqxx::result Delete(const StringUnMap &Fields) = 0;

  virtual Json SerializeModel() = 0;
};

#endif