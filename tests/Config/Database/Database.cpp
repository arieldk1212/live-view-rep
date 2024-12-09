#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

/*
 * Database Test's
 */

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
  EXPECT_EQ(response.capacity(), 0); // INFO: only 1 row with id = 1.
}

/*
 * DatabaseModel Test's
 */

TEST(DatabaseModel, DatabaseModelCreation) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();

  StringMap Fields;
  Fields.emplace("AddressName", "text");
  Fields.emplace("AddressNumber", "int");
  Manager->AddModel("Address", Fields);
  std::string Response = Manager->PrintModel("Address");

  StringMap TestFields;
  TestFields.emplace("TestName", "Text");
  Manager->AddModel("Test", TestFields);
  std::string ResponseTest = Manager->PrintModel("Test");

  EXPECT_STRNE(ResponseTest.c_str(), Response.c_str());
}

TEST(DatabaseModel, DatabaseModelAddField) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();

  StringMap Fields;
  Fields.emplace("AddressName", "text");
  Manager->AddModel("Address", Fields);
  std::string Response = Manager->PrintModel("Address");

  Manager->AddField("Address", "AddedField", "Text");
  std::string AddedFieldResponse = Manager->PrintModel("Address");

  EXPECT_STRNE(Response.c_str(), AddedFieldResponse.c_str());
}

TEST(DatabaseModel, DatabaseModelSwapFields) {
  std::shared_ptr<DatabaseManager> Manager =
      std::make_shared<DatabaseManager>();

  StringMap PreFields;
  PreFields.emplace("AddressName", "text");
  PreFields.emplace("AddressNumber", "int");
  Manager->AddModel("Address", PreFields);
  std::string PreResponse = Manager->PrintModel("Address");

  StringMap PostFields;
  PostFields.emplace("PostAddressName", "text");
  Manager->SwapAllFields("Address", PostFields);
  std::string PostResponse = Manager->PrintModel("Address");

  EXPECT_STRNE(PreResponse.c_str(), PostResponse.c_str());
}