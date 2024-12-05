#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <map>

typedef std::map<std::string, std::string> StringMap;

class DatabaseModel {
public:
  DatabaseModel(const std::string &ModelTabelName, const StringMap &ModelFields);
  ~DatabaseModel() = default;

  std::string StringSerialization();
  std::string QuerySerialization();
  uint64_t GetObjectUUID();

  void InsertField(const std::string &FieldType, const std::string &FieldValue);
  DatabaseModel &GetDatabaseModel() const; // INFO: for vector iteration.

private:
  std::string m_DatabaseModelString;
  std::string m_DatabaseModelTableName;
  StringMap m_DatabaseModelFields;
};

#endif