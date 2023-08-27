#include "SunCoordinatesMotion.h"
#include "Utils.h"

namespace sunmoon
{
SunCoordinatesMotion::SunCoordinatesMotion(double raDayM1, double decDayM1, double raDay0, double decDay0, double raDayP1, double decDayP1) : angleRADayM1(raDayM1), angleDecDayM1(decDayM1), angleRADay0(raDay0), angleDecDay0(decDay0), angleRADayP1(raDayP1), angleDecDayP1(decDayP1)
{
}

double SunCoordinatesMotion::getAngleRADayM1() const
{
	return angleRADayM1;
}

double SunCoordinatesMotion::getAngleDecDayM1() const
{
	return angleDecDayM1;
}

double SunCoordinatesMotion::getAngleRADay0() const
{
	return angleRADay0;
}

double SunCoordinatesMotion::getAngleDecDay0() const
{
	return angleDecDay0;
}

double SunCoordinatesMotion::getAngleRADayP1() const
{
	return angleRADayP1;
}

double SunCoordinatesMotion::getAngleDecDayP1() const
{
	return angleDecDayP1;
}

void SunCoordinatesMotion::setAngleRADayM1(double value)
{
	angleRADayM1 = value;
}

void SunCoordinatesMotion::setAngleRADay0(double value)
{
	angleRADay0 = value;
}

void SunCoordinatesMotion::setAngleRADayP1(double value)
{
	angleRADayP1 = value;
}
} // namespace sunmoon
