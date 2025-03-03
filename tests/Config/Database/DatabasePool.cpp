#include "../../../inc/Config/DatabasePool.h"
#include "../../Test.h"

#include <future>
#include <gtest/gtest.h>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

class DatabasePoolTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabasePool> Manager;

  void SetUp() override {
    std::string TestDatabaseConnectionString;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
    }
    Manager =
        std::make_shared<DatabasePool>(std::move(TestDatabaseConnectionString));
  }
};

TEST_F(DatabasePoolTest, DatabasePoolCreationTest) {
  auto conn = Manager->GetConnection();
  auto Status = conn->IsDatabaseConnected();
  auto Result = conn->GetConnectionString();
  Manager->ReturnConnection(conn);

  EXPECT_FALSE(Result.empty());
  EXPECT_GT(Result.length(), 5);
  EXPECT_TRUE(Status);
}

TEST_F(DatabasePoolTest, DatabasePoolTest) {
  auto conn1 = Manager->GetConnection();
  auto conn2 = Manager->GetConnection();
  auto conn3 = Manager->GetConnection();
  auto conn4 = Manager->GetConnection();
  auto conn5 = Manager->GetConnection();
  auto conn6 = Manager->GetConnection();
  auto conn7 = Manager->GetConnection();
  auto conn8 = Manager->GetConnection();
  auto conn9 = Manager->GetConnection();
  auto conn10 = Manager->GetConnection();

  auto size = Manager->GetConnectionsState();

  EXPECT_FALSE(size);
}

TEST_F(DatabasePoolTest, DatabaseMultiThreadTest) {
  std::thread Thread;
  for (int i = 0; i < 100; i++) {
  }
}