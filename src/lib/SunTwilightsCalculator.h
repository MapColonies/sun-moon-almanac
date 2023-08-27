#pragma once

#include "Location.h"
#include "DateTime.h"
#include "SunTwilightsData.h"
#include "InterpolationCalculator.h"
#include "SunCoordinates.h"
#include "RiseSetInfo.h"
#include "SunCoordinatesMotion.h"

// Dusk and Dawn is devided to 3 types of values
// 06 degrees below horizon - Civil Dusk and Dawn
// 12 degrees below horizon - Nautical Dusk and Dawn
// 18 degrees below horizon - Astronomical Dusk and Dawn
//
// Dawn and Dusk Azimuths occure when the center of the sun in on the horizon
namespace sunmoon
{
class SunTwilightsCalculator
{
  private:
	InterpolationCalculator interp1;
	SunCoordinates suncoo(const DateTime &dateTime);
	double lst(const DateTime &dateTime, double eastLong);
	double nutation(const DateTime &dateTime);
	RiseSetInfo riseSet(const SunCoordinatesMotion &motion0, const SunCoordinatesMotion &motionP, const SunCoordinatesMotion &motionM, double gast, double gastP, double gastM,
						int timeZone, double altitude, const Location &location, int deltaT);
	RiseSetInfo riseSet(const SunCoordinatesMotion &motion, double gast, double altitude, const Location &location, int deltaT);

  public:
	SunTwilightsData calculate(const Location &location, const DateTime &dateTime);
};
} // namespace sunmoon
