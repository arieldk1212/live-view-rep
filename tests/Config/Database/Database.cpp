#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

#include <memory>

class DatabaseTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> Manager;
  StringMap TestFieldsFirst;
  StringMap TestFieldsSecond;

  void SetUp() override {
    GlobalConfig::InitGlobalConfig("../../config.json");
    std::string TestDatabaseConnectionString =
        GlobalConfig::g_Config->DatabaseToString();
    Manager = std::make_shared<DatabaseManager>(TestDatabaseConnectionString);
  }

  void TearDown() override {
    Manager.reset();
    TestFieldsFirst.clear();
    TestFieldsSecond.clear();
  }
};

TEST_F(DatabaseTest, DatabaseConnectionTest) {
  bool Result = Manager->DatabaseConnectionValidation();
  EXPECT_TRUE(Result);
}

TEST_F(DatabaseTest, DatabaseModelCreation) {
  TestFieldsFirst.emplace("AddressName", "text");
  TestFieldsFirst.emplace("AddressNumber", "int");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string Response = Manager->PrintModel("Address");

  TestFieldsSecond.emplace("TestName", "Text");
  Manager->AddModel("Test", TestFieldsSecond);
  std::string ResponseTest = Manager->PrintModel("Test");

  EXPECT_STRNE(ResponseTest.c_str(), Response.c_str());
}

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string Response = Manager->PrintModel("Address");

  Manager->AddField("Address", "AddedField", "Text");
  std::string AddedFieldResponse = Manager->PrintModel("Address");

  EXPECT_STRNE(Response.c_str(), AddedFieldResponse.c_str());
}

TEST_F(DatabaseTest, DatabaseModelSwapFields) {
  TestFieldsFirst.emplace("AddressName", "text");
  TestFieldsFirst.emplace("AddressNumber", "int");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string PreResponse = Manager->PrintModel("Address");

  TestFieldsSecond.emplace("PostAddressName", "text");
  Manager->SwapAllFields("Address", TestFieldsSecond);
  std::string PostResponse = Manager->PrintModel("Address");

  EXPECT_STRNE(PreResponse.c_str(), PostResponse.c_str());
}

TEST_F(DatabaseTest, DatabaseModelCreateMethodTest) {
  /**
   * @brief can also be written like so ->
   *    TestFieldsFirst.emplace("created_at", "timestamp");
   *    TestFieldsFirst.emplace("addressnumber", "int");
   */
  TestFieldsFirst.insert({
      {"id", "serial primary key"},
      {"addressname", "varchar(100)"},
      {"addresslocation", "varchar(100)"},
      {"addressnumber", "int"},
  });

  auto MethodResponse = Manager->AddModel("Address", TestFieldsFirst);

  EXPECT_NE(MethodResponse.query().size(), 0);
}