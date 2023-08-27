#include "RiseSetInfo.h"

namespace sunmoon
{
double RiseSetInfo::getRiseAzimuth() const
{
	return riseAzimuth;
}

double RiseSetInfo::getSetAzimuth() const
{
	return setAzimuth;
}

double RiseSetInfo::getRiseTime() const
{
	return riseTime;
}

double RiseSetInfo::getSetTime() const
{
	return setTime;
}

double RiseSetInfo::getTransitTime() const
{
	return transitTime;
}

void RiseSetInfo::setRiseTime(double newRiseTime)
{
	riseTime = newRiseTime;
}

void RiseSetInfo::setTransitTime(double newTransitTime)
{
	transitTime = newTransitTime;
}

void RiseSetInfo::setSetTime(double newSetTime)
{
	setTime = newSetTime;
}

void RiseSetInfo::setRiseAzimuth(double newRiseAzimuth)
{
	riseAzimuth = newRiseAzimuth;
}

void RiseSetInfo::setSetAzimuth(double newSetAzimuth)
{
	setAzimuth = newSetAzimuth;
}

void RiseSetInfo::addTimeZone(int timeZone)
{
	riseTime += (timeZone / 24.0);
	setTime += (timeZone / 24.0);
	transitTime += (timeZone / 24.0);
}
} // namespace sunmoon
