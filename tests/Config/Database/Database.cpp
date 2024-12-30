#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"
#include "Config/DatabaseCommands.h"

#include <memory>

class DatabaseTest : public ::testing::Test {
protected:
  std::shared_ptr<DatabaseManager> Manager;
  StringUnMap TestFieldsFirst;
  StringUnMap TestFieldsSecond;

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
  std::string Response = Manager->GetModelData("Address");

  TestFieldsSecond.emplace("TestName", "Text");
  Manager->AddModel("Test", TestFieldsSecond);
  std::string ResponseTest = Manager->GetModelData("Test");

  EXPECT_STRNE(ResponseTest.c_str(), Response.c_str());
}

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string Response = Manager->GetModelData("Address");

  Manager->AddField("Address", "AddedField", "Text");
  std::string AddedFieldResponse = Manager->GetModelData("Address");

  EXPECT_STRNE(Response.c_str(), AddedFieldResponse.c_str());
}

TEST_F(DatabaseTest, DatabaseModelSwapFields) {
  TestFieldsFirst.emplace("AddressName", "text");
  TestFieldsFirst.emplace("AddressNumber", "int");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string PreResponse = Manager->GetModelData("Address");

  TestFieldsSecond.emplace("PostAddressName", "text");
  Manager->SwapAllFields("Address", TestFieldsSecond);
  std::string PostResponse = Manager->GetModelData("Address");

  EXPECT_STRNE(PreResponse.c_str(), PostResponse.c_str());
}

TEST_F(DatabaseTest, DatabaseModelCreateMethodTest) {
  /**
   * @brief can also be written like so ->
   *    TestFieldsFirst.emplace("created_at", "timestamp");
   *    TestFieldsFirst.emplace("addressnumber", "int");
   */
  TestFieldsFirst.insert({
      {"id",
       DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
      {"addressname",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addresslocation",
       DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
      {"addressnumber",
       DatabaseCommandToString(DatabaseFieldCommands::IntField)},
  });

  auto MethodResponse = Manager->AddModel("Address", TestFieldsFirst);

  EXPECT_NE(MethodResponse.query().size(), 0);
}