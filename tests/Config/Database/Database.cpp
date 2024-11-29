#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

TEST(Database, DatabaseConnectionTest) {
  std::shared_ptr<DatabaseManager> Manager =
    std::make_shared<DatabaseManager>();
  bool Result = Manager->DatabaseConnectionValidation();
  EXPECT_EQ(Result, true);
}

TEST(Database, DatabaseExecuteQuery) {
  std::shared_ptr<DatabaseManager> Manager =
    std::make_shared<DatabaseManager>();
  std::string command = "create table if not exists logger(id serial primary key, logfile text, timestamp text, msg text)";
  std::string_view response;
  response = Manager->Execute(command);
  std::cout << response;
  EXPECT_EQ(response.data(), "") << " was " << response;
}