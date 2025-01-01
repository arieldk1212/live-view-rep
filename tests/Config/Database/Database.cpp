#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

#include <gtest/gtest.h>
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
  std::string Response = Manager->GetSerializedModelData("Address");

  TestFieldsSecond.emplace("TestName", "Text");
  Manager->AddModel("Test", TestFieldsSecond);
  std::string ResponseTest = Manager->GetSerializedModelData("Test");

  EXPECT_STRNE(ResponseTest.c_str(), Response.c_str());
}

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string Response = Manager->GetSerializedModelData("Address");

  Manager->AddField("Address", "AddedField", "Text");
  std::string AddedFieldResponse = Manager->GetSerializedModelData("Address");

  EXPECT_STRNE(Response.c_str(), AddedFieldResponse.c_str());
}

TEST_F(DatabaseTest, DatabaseModelSwapFields) {
  TestFieldsFirst.emplace("AddressName", "text");
  TestFieldsFirst.emplace("AddressNumber", "int");
  Manager->AddModel("Address", TestFieldsFirst);
  std::string PreResponse = Manager->GetSerializedModelData("Address");

  TestFieldsSecond.emplace("PostAddressName", "text");
  Manager->SwapAllFields("Address", TestFieldsSecond);
  std::string PostResponse = Manager->GetSerializedModelData("Address");

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

TEST_F(DatabaseTest, DatabaseModelGetSerializedDataTest) {
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
  auto Data = Manager->GetSerializedModelData("Address");

  EXPECT_NE(Data.find("id"), 0);
}

TEST_F(DatabaseTest, DatabaseModelGetDataTest) {
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
/** @todo fix this test, then move to other tests, add dtor in the gtest, finish migrate. */
  auto MethodResponse = Manager->AddModel("Address", TestFieldsFirst);
  auto Data = Manager->GetModelData("Address");

  EXPECT_FALSE(Data.empty());
}

TEST_F(DatabaseTest, DatabaseRemoveModelTest) {
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
  auto Data = Manager->RemoveModel("Address");
  auto ModelData = Manager->GetSerializedModelData("Address");

  // EXPECT_TRUE(Data.column_table("Address")) << ModelData;
  EXPECT_EQ(ModelData.length(), 0) << ModelData;
}