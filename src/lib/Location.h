#pragma once

#include <string>

// Represents DMS location in WGS84 Geo Coordinate system
namespace sunmoon
{
class Location
{
  private:
	double lon; // Seconds
	double lat; // Seconds
	double height;

  public:
	Location(double lonDegree, double lonMinutes, double lonSeconds, double latDegree, double latMinutes, double latSeconds, double h = 0);
	Location(double lonDegree, double latDegree, double h = 0);
	double getLonDegree() const;
	double getLatDegree() const;
	double getHeight() const;
	double getLonRadians() const;
	double getLatRadians() const;
	std::string toString() const;
};
} // namespace sunmoon