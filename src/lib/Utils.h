#pragma once
#include "DMS.h"
#include "DateTime.h"
#include "SunCoordinates.h"

namespace sunmoon
{
const double PI = 3.14159265358979323846264338328;
const double RADIAN = 180 / PI;

class Utils
{
  private:
	// Calculate the Nutation in longitude
	static double nutation(const DateTime &dateTime);

  public:
	static double degreeToRad(double seconds);
	static double radToDegree(double rad);
	static DMS degreeToDms(double degree);
	static double obliquity(const DateTime &dateTime);

	// Local Sidereal Time, (mean or apparent), for vector of JD's and a given East Longitude(In radians).
	static double lst(const DateTime &dateTime, double eastLong, bool calcNutation = true);
	static SunCoordinates suncoo(const DateTime &dateTime);
};
} // namespace sunmoon