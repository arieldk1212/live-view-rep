#include "../../../inc/Core/Location/Geolocation.h"
#include "../../Test.h"


class GeolocationTest : public ::testing::Test {
protected:
  Geolocation location {35.689487, 139.691711};
};

TEST_F(GeolocationTest, GeolocationPlusCodeTest) {
  auto result = location.GetPlusCode();
  EXPECT_NE(result, "Not Valid");
}

TEST_F(GeolocationTest, GeolocationSizeOfTest) {
  EXPECT_NE(sizeof(location), 0);
}

TEST_F(GeolocationTest, GeolocationCoordinatesTest) {
  EXPECT_GT(sizeof(location.GetFormattedCoordinates()), 10);
}