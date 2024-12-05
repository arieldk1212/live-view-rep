#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <map>

typedef std::unordered_map<std::string, std::string> StringMap;

class DatabaseModel {
public:
  DatabaseModel(
      const std::string &ModelTabelName); // TODO: upon new model creation,
                                          // create a new table in the db.
  ~DatabaseModel() = default;

  std::string StringSerialization();
  std::string QuerySerialization();
  uint64_t GetObjectUUID();

  void InsertField(const std::string &FieldType, const std::string &FieldValue);
  DatabaseModel &GetDatabaseModel() const; // INFO: for vector iteration.

private:
  std::string m_DatabaseModelString;
  std::string m_DatabaseModelTableName;
  std::map<std::string, std::string> m_DatabaseModelFields;
};

#endif