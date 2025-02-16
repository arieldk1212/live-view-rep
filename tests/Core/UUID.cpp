#include "../../inc/Core/UUID.h"
#include "../Test.h"

#include <cstddef>
#include <cstdint>

class UUIDTest : public ::testing::Test {
protected:
  UUID uuid_test;
  const uint64_t test = 123123;
};

TEST_F(UUIDTest, UUIDValidateType) {
  EXPECT_EQ(typeid(uuid_test.GetUUID()), typeid(test));
}

TEST_F(UUIDTest, UUIDVisualValueTest) { 
  EXPECT_EQ(sizeof(uuid_test.GetUUID()), 8) << uuid_test.GetUUID();
}