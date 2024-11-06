#ifndef GEO_H
#define GEO_H

#include <string>

// TODO: init the private fields for lat/lon

class Geometry {
public:
  Geometry();
  ~Geometry() = default;

  std::string FormattedGeo();

private:
  std::string m_Longitude;
  std::string m_Latitude;
};

#endif //GEO_H
