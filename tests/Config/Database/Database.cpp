#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

#include <memory>
#include <stdio.h>
#include <stdlib.h>

class DatabaseTest : public ::testing::Test {
protected:
  std::string TestTableName;
  std::shared_ptr<DatabaseManager> Manager;
  StringUnMap TestFieldsFirst;
  StringUnMap TestFieldsSecond;

  void SetUp() override {
    std::string TestDatabaseConnectionString;
    if (std::getenv("GITHUB_ACTIONS") != nullptr) {
      GlobalConfig::InitGlobalConfig("../../ci-config.json");
      TestDatabaseConnectionString =
          GlobalConfig::g_Config->TestDatabaseToString();
    } else {
      GlobalConfig::InitGlobalConfig("../../config.json");
      TestDatabaseConnectionString =
          GlobalConfig::g_Config->TestDatabaseToString();
    }
    Manager = std::make_shared<DatabaseManager>(TestDatabaseConnectionString);
    TestTableName = "Test";
  }

  void TearDown() override {
    Manager->RemoveModel("Test");
    Manager.reset();
    TestFieldsFirst.clear();
    TestFieldsSecond.clear();
  }
};

TEST_F(DatabaseTest, DatabaseModelCreation) {
  TestFieldsFirst.emplace("AddressName", "text");
  TestFieldsFirst.emplace("AddressNumber", "int");
  Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Response = Manager->GetSerializedModelData(TestTableName);

  TestFieldsSecond.emplace("TestName", "Text");
  Manager->AddModel("Test2", TestFieldsSecond);
  auto ResponseTest = Manager->GetSerializedModelData("Test2");
  Manager->RemoveModel("Test2");

  EXPECT_STRNE(ResponseTest.c_str(), Response.c_str());
}

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel(TestTableName, TestFieldsFirst);
  std::string Response = Manager->GetSerializedModelData(TestTableName);

  Manager->AddColumn(TestTableName, "AddedField", "Text");
  std::string AddedFieldResponse =
      Manager->GetSerializedModelData(TestTableName);

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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);

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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Data = Manager->GetSerializedModelData(TestTableName);

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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName);

  EXPECT_NE(Response.affected_rows(), 0);
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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName, "id", "1");

  EXPECT_NE(Response.affected_rows(), 0);
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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Before = Manager->GetModelData(TestTableName);
  auto Response = Manager->TruncateModel(TestTableName);
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before, After);
}

// TEST_F(DatabaseTest, DatabaseRemoveModelTest) {
//   TestFieldsFirst.insert({
//       {"id",
//        DatabaseCommandToString(DatabaseFieldCommands::SerialPrimaryKeyField)},
//       {"addressname",
//        DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
//       {"addresslocation",
//        DatabaseCommandToString(DatabaseFieldCommands::VarChar100Field)},
//       {"addressnumber",
//        DatabaseCommandToString(DatabaseFieldCommands::IntField)},
//   });

//   auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);

//   EXPECT_TRUE(MethodResponse.());
// }

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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->AddColumn(TestTableName, "testfield", "int");
  auto Data = Manager->GetSerializedModelData(TestTableName);

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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto PreData = Manager->GetSerializedModelData(TestTableName);
  Manager->DropColumn(TestTableName, "id");
  auto AfterData = Manager->GetSerializedModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

TEST_F(DatabaseTest, DatabaseAlterColumnTest) {
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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto PreData = Manager->GetSerializedModelData(TestTableName);
  Manager->AlterColumn(
      TestTableName, "addressname",
      DatabaseCommandToString(DatabaseFieldCommands::CharField));
  auto AfterData = Manager->GetSerializedModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

TEST_F(DatabaseTest, DatabaseInsertIntoTest) {
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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto Response = Manager->GetModelData(TestTableName);

  EXPECT_NE(Response.affected_rows(), 0);
}

TEST_F(DatabaseTest, DatabaseUpdateColumnTest) {
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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto PreData = Manager->GetModelData(TestTableName);
  Manager->UpdateColumn(TestTableName, "addressname", "holon", "id=1");
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}

TEST_F(DatabaseTest, DatabaseUpdateColumnsTest) {
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

  StringUnMap Data = {{"addressname", "rami"},
                      {"addresslocation", "levi"},
                      {"addressnumber", "18"},
                      {"id", "1"}};

  StringUnMap NewFields = {{"addressname", "new"},
                           {"addresslocation", "fields"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  Manager->InsertInto(TestTableName, Data);
  auto PreData = Manager->GetModelData(TestTableName);
  Manager->UpdateColumns(TestTableName, NewFields, "id=1");
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}