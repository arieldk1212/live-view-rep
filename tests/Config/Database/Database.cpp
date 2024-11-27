#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

TEST(Database, DatabaseConnectionTest) {
  std::shared_ptr<DatabaseManager> Manager =
    std::make_shared<DatabaseManager>();
  bool Result = Manager->DatabaseConnectionValidation();
  EXPECT_EQ(Result, true);
}