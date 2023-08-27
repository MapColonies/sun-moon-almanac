#include "SunCoordinates.h"
#include "Utils.h"

namespace sunmoon
{
SunCoordinates::SunCoordinates(double ra, double dec) : angleRA(ra < 0 ? 2 * PI + ra : ra), angleDec(dec)
{
}

double SunCoordinates::getAngleRA() const
{
	return angleRA;
}

double SunCoordinates::getAngleDec() const
{
	return angleDec;
}
} // namespace sunmoon
