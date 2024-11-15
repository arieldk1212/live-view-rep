#ifndef GEO_H
#define GEO_H

#include <string>

// TODO: init the private fields for lat/lon.
// TODO: Create the plus codes class, maybe use pure virtual class for Location.

class Geo {
public:
	Geo();
	~Geo() = default;

	std::string FormattedGeo();

private:
	std::string m_Longitude;
	std::string m_Latitude;
};

#endif // GEO_H
