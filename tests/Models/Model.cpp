#include "Models/Model.h"
#include "../Test.h"

class ModelTest : public ::testing::Test {
protected:
  std::unique_ptr<Model::Schemes> scheme;

  void SetUp() override { scheme = std::make_unique<Model::Schemes>(); }

  void TearDown() override { scheme.reset(); }
};

TEST_F(ModelTest, ModelStatusTest) {
  auto SchemeLog = scheme->GetSchema("Log");
  auto ResultLog = SchemeLog.contains("logid");

  auto SchemeAddress = scheme->GetSchema("Address");
  auto ResultAddress = SchemeAddress.contains("addressid");

  auto SchemeAddressLog = scheme->GetSchema("AddressLog");
  auto ResultAddressLog = SchemeAddressLog.contains("addressid");

  auto SchemeAddressLocation = scheme->GetSchema("AddressLocation");
  auto ResultAddressLocation = SchemeAddressLocation.contains("addressid");

  EXPECT_TRUE(ResultLog);
  EXPECT_TRUE(ResultAddress);
  EXPECT_TRUE(ResultAddressLog);
  EXPECT_TRUE(ResultAddressLocation);
}

TEST_F(ModelTest, ModelSchemesTest) {
  auto Scheme = scheme->GetSchemes();

  EXPECT_TRUE(Scheme.contains("Log"));
  EXPECT_TRUE(Scheme.contains("Address"));
  EXPECT_TRUE(Scheme.contains("AddressLog"));
  EXPECT_TRUE(Scheme.contains("AddressLocation"));
}