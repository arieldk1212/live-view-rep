#include "../../../inc/Config/DatabaseManager.h"
#include "../../Test.h"

#include <future>
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
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/ci-config.json");
    } else {
      TestDatabaseConnectionString =
          Config::TestDatabaseToString("../../configs/config.json");
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

TEST_F(DatabaseTest, DatabaseModelAddField) {
  TestFieldsFirst.emplace("AddressName", "text");
  Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AddColumn(TestTableName, "AddedField", "Text");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
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

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);

  EXPECT_NE(MethodResponse.query().size(), 0);
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
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AddColumn(TestTableName, "testfield", "int");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
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
  auto Before = Manager->GetModelData(TestTableName);
  Manager->DropColumn(TestTableName, "id");
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.columns(), After.columns());
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

  StringUnMap PostData = {{"addressname", "20"},
                          {"addresslocation", "levi"},
                          {"addressnumber", "18"},
                          {"id", "1"}};

  auto MethodResponse = Manager->AddModel(TestTableName, TestFieldsFirst);
  auto Before = Manager->GetModelData(TestTableName);
  Manager->AlterColumn(
      TestTableName, "addressname",
      DatabaseCommandToString(DatabaseFieldCommands::IntField));
  Manager->InsertInto(TestTableName, PostData);
  auto After = Manager->GetModelData(TestTableName);

  EXPECT_NE(Before.affected_rows(), After.affected_rows());
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
  auto size = NewFields.size();
  auto AfterData = Manager->GetModelData(TestTableName);

  EXPECT_NE(AfterData, PreData);
}