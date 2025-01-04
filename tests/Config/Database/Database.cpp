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

  Manager->AddColumn("Address", "AddedField", "Text");
  std::string AddedFieldResponse = Manager->GetSerializedModelData("Address");

  EXPECT_STRNE(Response.c_str(), AddedFieldResponse.c_str());
}

// TEST_F(DatabaseTest, DatabaseModelSwapFields) {
//   TestFieldsFirst.emplace("AddressName", "text");
//   TestFieldsFirst.emplace("AddressNumber", "int");
//   Manager->AddModel("Address", TestFieldsFirst);
//   std::string PreResponse = Manager->GetSerializedModelData("Address");

//   TestFieldsSecond.emplace("PostAddressName", "text");
//   Manager->SwapAllColumns("Address", TestFieldsSecond);
//   std::string PostResponse = Manager->GetSerializedModelData("Address");

//   EXPECT_STRNE(PreResponse.c_str(), PostResponse.c_str());
// }

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
  auto MethodResponse = Manager->AddModel("Address", TestFieldsFirst);
  /** @todo after insert into function is applied, add it here to make the test
   * complete. */
  auto Data = Manager->GetModelData("Address");

  EXPECT_NE(Data.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseModelGetDataByFieldTest) {
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
  /** @todo after insert into function is applied, add it here to make the test
   * complete. */
  auto Data = Manager->GetModelData("Address", "id", "1");

  EXPECT_NE(Data.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseTruncateModelTest) {
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
  /** @todo after insert into function is applied, add it here to make the test
   * complete. */
  auto Before = Manager->GetModelData("Address");
  auto Data = Manager->TruncateModel("Address");
  auto After = Manager->GetModelData("Address");

  EXPECT_NE(Before, After);
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

  EXPECT_TRUE(Data.empty());
}

TEST_F(DatabaseTest, DatabaseAddColumnTest) {
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
  Manager->AddColumn("Address", "testfield", "int");
  auto Data = Manager->GetSerializedModelData("Address");

  EXPECT_TRUE(Data.find("testfield"));
}

TEST_F(DatabaseTest, DatabaseDropColumnTest) {
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
  Manager->DropColumn("Address", "id");
  auto Data = Manager->GetSerializedModelData("Address");

  EXPECT_FALSE(Data.find("id")) << Data;
}