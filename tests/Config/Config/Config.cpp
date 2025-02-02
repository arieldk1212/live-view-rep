#include "../../Test.h"

class ConfigTest : public ::testing::Test {
protected:
    std::string TestDataString;

  void SetUp() override {
    TestDataString = Config::TestDatabaseToString("../../configs/config.json");
  }

  void TearDown() override {}
};

TEST_F(ConfigTest, ConfigOverallTest){
  std::string GoodDataString = "user=arielkriheli password=password "
                                "host=localhost port=5432 dbname=live_view_test";
  EXPECT_EQ(TestDataString, GoodDataString);
}