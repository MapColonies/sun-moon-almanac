#include "MoonCoordinates.h"

namespace sunmoon
{
	MoonCoordinates::MoonCoordinates(double ra, double dec, double hp) : moonRA(ra), moonDec(dec), moonHP(hp)
	{
	}

	double MoonCoordinates::getMoonRA() const
	{
		return moonRA;
	}

	double MoonCoordinates::getMoonDec() const
	{
		return moonDec;
	}

	double MoonCoordinates::getMoonHP() const
	{
		return moonHP;
	}
} // namespace sunmoon
