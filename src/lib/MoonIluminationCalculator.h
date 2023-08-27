#pragma once
#include "Location.h"
#include "DateTime.h"
#include "MoonIluminationData.h"
#include "MoonCoordinates.h"

// Calculates moon position and ilumination at specific time
namespace sunmoon
{
class MoonIluminationCalculator
{
  private:
	MoonCoordinates getMoonCoordinates(const Location &location, const DateTime &dateTime);
	void monecool(const DateTime &dateTime, double &lon, double &lat, double &hp);
	void calcHorizontalCoordinates(const MoonCoordinates &moonCoordinates, const DateTime &dateTime, const Location &location, double &horizAz, double &horizAlt);
	double calcMoonLight(double moonAlt, double moonHP, double moonElon);

  public:
	MoonIluminationData calculate(const Location &location, const DateTime &dateTime);
};
} // namespace sunmoon
