#ifndef GEOLOCATION_H
#define GEOLOCATION_H

#include <string>

/**
 * @brief this file is responsible for the image, address geolocation, verification, also verifying with a gps.
 * also, add the plus codes functionallity to this class.
 */

class Geolocation {
public:
	Geolocation();
	~Geolocation() = default;

	std::string FormattedGeo();

private:
	std::string m_Longitude;
	std::string m_Latitude;
};

#endif