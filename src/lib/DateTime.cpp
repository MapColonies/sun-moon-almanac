#include "DateTime.h"
#include <algorithm>
#include <math.h>

using namespace std;

namespace sunmoon
{
int DateTime::timeZoneDelta = 0;

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
	double fraction = hour + minute / 60.0 + second / 3600.0;

	double a = floor((14 - month) / 12);
	year = year + 4800 - a;
	month = month + 12 * a - 3;

	julianTime = day + floor((153 * month + 2) / 5) + 365 * year + floor(year / 4) - floor(year / 100) + floor(year / 400) - 32045 + ((fraction - 12) / 24);
}

DateTime::DateTime(double otherJulianTime) : julianTime(otherJulianTime)
{
}

double DateTime::getJulianTime() const
{
	return julianTime;
}

DateTime DateTime::addDays(int days) const
{
	return DateTime(julianTime + days);
}

DateTime DateTime::minusHours(int hours) const
{
	return DateTime(julianTime - ((hours - 12) / 24));
}

int DateTime::getTimeZone()
{
	return timeZoneDelta;
}

void DateTime::setTimeZone(int tz)
{
	timeZoneDelta = tz;
}
} // namespace sunmoon