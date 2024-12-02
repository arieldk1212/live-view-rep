#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"

#include <unordered_map>

template <class T> class DatabaseModel {
public:
  DatabaseModel(); // TODO: upon new model creation, create a new table in the db.
  ~DatabaseModel() = default;

  struct QueryActions {
    void Create();
    void Read();
    void Insert();
    void Update();
    void Delete();
  };

  void InsertField(const T &FieldType, const T &FieldValue);
  std::string StringSerialization();
  std::string QuerySerialization();
  uint64_t GetObjectUUID();

private:
  int m_DatabaseModelSize;
  std::string m_DatabaseModelString;
  std::string m_DatabaseModelTableName;
  std::unordered_map<T, T>
      m_DatabaseModelFields; // Example: text -> text value.
};

// TODO: Manager->AddModel("LoggerModel", "fields") for example, creates the
// model that we want to create, puts it in the manager in a vector full of
// models and in every Model we can use the methods we created in DatabaseModel
// class.

#endif