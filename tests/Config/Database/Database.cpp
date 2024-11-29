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
  std::string command = "create table if not exists logger(id serial primary key, logfile text, timestamp text, msg text)";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.query(), command);
}

TEST(Database, DatabaseInsertTableQuery) {
  std::shared_ptr<DatabaseManager> Manager =
    std::make_shared<DatabaseManager>();
  std::string command = "insert into logger (logfile, timestamp, msg) values ('test', 'now', 'testttt');";
  auto response = Manager->Query(command);
  EXPECT_EQ(response.query(), command);
}