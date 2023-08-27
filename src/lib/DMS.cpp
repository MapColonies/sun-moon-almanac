#include "DMS.h"

using namespace std;

namespace sunmoon
{
	DMS::DMS(int d, int m, int s) : degrees(d), minutes(m), seconds(s)
	{
	}

	DMS::DMS() : degrees(0), minutes(0), seconds(0)
	{
	}

	int DMS::getDegrees() const
	{
		return degrees;
	}

	int DMS::getMinutes() const
	{
		return minutes;
	}

	int DMS::getSeconds() const
	{
		return seconds;
	}

	string DMS::toString() const
	{
		return "(" + to_string(degrees) + ":" + to_string(minutes) + ":" + to_string(seconds) + ")";
	}
} // namespace sunmoon
