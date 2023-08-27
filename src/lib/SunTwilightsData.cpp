#include "SunTwilightsData.h"

using namespace std;

namespace sunmoon
{
void SunTwilightsData::setDawnAzimuth(double dawnAzimuthValue)
{
	dawnAzimuth = dawnAzimuthValue;
}

void SunTwilightsData::setDuskAzimuth(double duskAzimuthValue)
{
	duskAzimuth = duskAzimuthValue;
}

void SunTwilightsData::setRiseTime(DMS riseTimeValue)
{
	riseTime = riseTimeValue;
}

void SunTwilightsData::setSetTime(DMS setTimeValue)
{
	setTime = setTimeValue;
}

void SunTwilightsData::setDawnTime06(DMS dawnTime06Value)
{
	dawnTime06 = dawnTime06Value;
}

void SunTwilightsData::setDawnTime12(DMS dawnTime12Value)
{
	dawnTime12 = dawnTime12Value;
}

void SunTwilightsData::setDawnTime18(DMS dawnTime18Value)
{
	dawnTime18 = dawnTime18Value;
}

void SunTwilightsData::setDuskTime06(DMS duskTime06Value)
{
	duskTime06 = duskTime06Value;
}

void SunTwilightsData::setDuskTime12(DMS duskTime12Value)
{
	duskTime12 = duskTime12Value;
}

void SunTwilightsData::setDuskTime18(DMS duskTime18Value)
{
	duskTime18 = duskTime18Value;
}

double SunTwilightsData::getDawnAzimuth() const
{
	return dawnAzimuth;
}

double SunTwilightsData::getDuskAzimuth() const
{
	return duskAzimuth;
}

DMS SunTwilightsData::getRiseTime() const
{
	return riseTime;
}

DMS SunTwilightsData::getSetTime() const
{
	return setTime;
}

DMS SunTwilightsData::getDawnTime06() const
{
	return dawnTime06;
}

DMS SunTwilightsData::getDawnTime12() const
{
	return dawnTime12;
}

DMS SunTwilightsData::getDawnTime18() const
{
	return dawnTime18;
}

DMS SunTwilightsData::getDuskTime06() const
{
	return duskTime06;
}

DMS SunTwilightsData::getDuskTime12() const
{
	return duskTime12;
}

DMS SunTwilightsData::getDuskTime18() const
{
	return duskTime18;
}

std::string SunTwilightsData::toString() const
{
	return "Azimuth[dawn:" + to_string(dawnAzimuth) + ", dusk:" + to_string(duskAzimuth) + "]\n" +
		   "Rise: " + riseTime.toString() + ", Set: " + setTime.toString() + "\n"
																			 "Dawn Transition[06: " +
		   dawnTime06.toString() + ", 12: " + dawnTime12.toString() + ", 18: " + dawnTime18.toString() + "]\n" +
		   "Dusk Transition[06: " + duskTime06.toString() + ", 12: " + duskTime12.toString() + ", 18: " + duskTime18.toString() + "]\n";
}
} // namespace sunmoon
