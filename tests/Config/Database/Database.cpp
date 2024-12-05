#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

TEST(Database, DatabaseConnectionTest) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  bool Result = Manager->DatabaseConnectionValidation();
  EXPECT_EQ(Result, true);
}

TEST(Database, DatabaseCreateTableQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "create table if not exists logger(id serial primary "
                        "key, logfile text, timestamp text, msg text)";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.query(), command);
}

TEST(Database, DatabaseInsertToTableQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "insert into logger (logfile, timestamp, msg) values "
                        "('test', 'now', 'testttt');";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.query(), command);
}

TEST(Database, DatabaseUpdateTableFieldQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "update logger set msg = 'newtest' where id = '1'";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.query(), command);
}

TEST(Database, DatabaseGetRowFromTableQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "select msg from logger where id = '1'";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.size(), 1); // INFO: only 1 row with id = 1.
}

TEST(Database, DatabaseGetValuesFromRowInTableQuery) {
  std::vector<std::string> values;
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "select * from logger where id = '1'";
  auto response = Manager->Query(command);
  for (auto row : response) {
    for (auto field : row) {
      values.emplace_back(field.c_str());
    }
  }
  EXPECT_EQ(values.size(), 4); // INFO: only 1 row with id = 1.
}

TEST(Database, DatabaseDeleteRowQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "delete from logger where id = '3'";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.capacity(), 0);
}

TEST(Database, DatabaseDropTableQuery) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  std::string command = "drop table logger";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.capacity(), 1); // INFO: only 1 row with id = 1.
}

TEST(DatabaseModel, DatabaseModelCreation) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();
  StringMap Fields;
  Manager->AddModel("Address", Fields);
  // TODO: add another field, remove, delete field,
  // then crud the model in the db itself.
}
