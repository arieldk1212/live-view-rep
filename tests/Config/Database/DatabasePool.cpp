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
  std::unique_ptr<DatabasePool> Manager;

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
        std::make_unique<DatabasePool>(std::move(TestDatabaseConnectionString));
  }

  void SingleThreadTask(std::string &ModelName) {
    auto ThreadConn = Manager->GetManagerConnection();
    auto ConnectionStatus = ThreadConn->IsDatabaseConnected();
    EXPECT_TRUE(ConnectionStatus);

    auto ConnectionString = ThreadConn->GetConnectionString();
    EXPECT_FALSE(ConnectionString.empty());
  }
};

TEST_F(DatabasePoolTest, DatabasePoolGeneralTest) {
  auto conn = Manager->GetManagerConnection();
  auto Status = conn->IsDatabaseConnected();
  auto String = conn->GetConnectionString();
  auto Size = Manager->GetCurrentPoolSize();
  auto MaxSize = Manager->GetPoolLimit();
  Manager->ReturnConnection(conn);
  auto AfterSize = Manager->GetCurrentPoolSize();

  EXPECT_TRUE(Status);
  EXPECT_FALSE(String.empty());
  EXPECT_GT(String.length(), 5);
  EXPECT_EQ(Size, 9);
  EXPECT_EQ(AfterSize, 10);
  EXPECT_EQ(MaxSize, 10);
}

TEST_F(DatabasePoolTest, DatabasePoolLimitTest) {
  // std::vector<DatabasePool::SharedManager> connections(Manager->GetManagerConnection(), 10);
  auto conn1 = Manager->GetManagerConnection();
  auto conn2 = Manager->GetManagerConnection();
  auto conn3 = Manager->GetManagerConnection();
  auto conn4 = Manager->GetManagerConnection();
  auto conn5 = Manager->GetManagerConnection();
  auto conn6 = Manager->GetManagerConnection();
  auto conn7 = Manager->GetManagerConnection();
  auto conn8 = Manager->GetManagerConnection();
  auto conn9 = Manager->GetManagerConnection();
  auto conn10 = Manager->GetManagerConnection();

  auto size = Manager->GetCurrentPoolSize();

  EXPECT_FALSE(size);
}

// TEST_F(DatabasePoolTest, DatabaseMultiThreadTest) {
//   auto MainConn = Manager->GetManagerConnection();
//   // MainConn->AddModel("address");
//   std::vector<std::thread> Threads;
//   Threads.reserve(20);
//   for (int i = 0; i < 100; i++) {
//     // Threads.emplace_back(SingleThreadTask(),
//     Manager->GetManagerConnection(), )
//   }
// }