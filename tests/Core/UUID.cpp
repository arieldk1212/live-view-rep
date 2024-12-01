#include "../../inc/Core/UUID.h"
#include "../Test.h"
#include <cstddef>

TEST(UUID, UUIDValidateType) {
  UUID uuid_test;
  const uint64_t test = 123123;
  EXPECT_EQ(typeid(uuid_test.GetUUID()), typeid(test));
}

TEST(UUID, UUIDVisualValueTest) { 
  UUID uuid_test; 
  EXPECT_EQ(sizeof(uuid_test.GetUUID()), 8) << uuid_test.GetUUID();
}