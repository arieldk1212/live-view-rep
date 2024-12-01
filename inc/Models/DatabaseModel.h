#ifndef DATABASE_MODEL_H
#define DATABASE_MODEL_H

#include "../Core/UUID.h"
#include "Config/DatabaseManager.h"

#include <unordered_map>

class DatabaseActions {
public:
  virtual ~DatabaseActions();
  virtual void Create();
  virtual void Read();
  virtual void Insert();
  virtual void Update();
  virtual void Delete();
};

template <class T> class DatabaseModel : public DatabaseActions {
public:
  DatabaseModel();
  ~DatabaseModel() override = default;

  void InsertDatabaseModelField(const T &FieldType, const T &FileValue);
  std::string StringSerialization();
  std::string QuerySerialization();
  uint64_t GetObjectUUID();

private:
  int m_DatabaseModelSize;
  std::string m_DatabaseModelString;
  std::unordered_map<T, T>
      m_DatabaseModelFields; // Example: text -> text value.
};

// INFO: DatabaseModel to basic methods for executing queries, than query
// class to define the fields and relate to a child Specific object
// model to quick insert data, than logger model for example to then execute
// neccessary data into the postgresdb.
// make a query decorator!!!

// TODO: Create basic model -> AbstractModel, then from that create an
// DatabaseModel with basic fields, then we add query for decoration.

#endif