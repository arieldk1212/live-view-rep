#include "../../../inc/Config/Config.h"
#include "../../Test.h"

class ConfigTest : public ::testing::Test {
protected:
  std::filesystem::path TestFilePath;
  std::string TestDataString;
  Json JsonData;

  void SetUp() override {
    Config Test {"../../config.json"};
    TestDataString = Test.DatabaseToString();
    JsonData = Test.GetData();
  }

  void TearDown() override {}
};

TEST_F(ConfigTest, ConfigOverallTest){
  std::string GoodDataString = "user=arielkriheli password=password "
                                "host=localhost port=5432 dbname=arielkriheli";
  EXPECT_EQ(TestDataString, GoodDataString);
}