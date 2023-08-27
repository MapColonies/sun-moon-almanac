#include "Location.h"
#include "Utils.h"

using namespace std;

namespace sunmoon
{
Location::Location(double lonDegree, double lonMinutes, double lonSeconds, double latDegree, double latMinutes, double latSeconds, double h)
{
	lon = lonDegree * 3600 + lonMinutes * 60 + lonSeconds;
	lat = latDegree * 3600 + latMinutes * 60 + latSeconds;
	height = h;
}

Location::Location(double lonDegree, double latDegree, double h) : lon(lonDegree * 3600), lat(latDegree * 3600), height(h)
{
}

double Location::getLonDegree() const
{
	return lon / 3600;
}

double Location::getLatDegree() const
{
	return lat / 3600;
}

double Location::getHeight() const
{
	return height;
}

double Location::getLonRadians() const
{
	return Utils::degreeToRad(getLonDegree());
}

double Location::getLatRadians() const
{
	return Utils::degreeToRad(getLatDegree());
}

std::string Location::toString() const
{
	return "Location[lon:" + to_string(getLonDegree()) + " lat:" + to_string(getLatDegree()) + "]";
}
} // namespace sunmoon