#include "Utils.h"
#include <algorithm>
#include <math.h>

namespace sunmoon
{
double Utils::degreeToRad(double seconds)
{
	return (seconds * PI) / 180;
}

double Utils::radToDegree(double rad)
{
	return (rad * 180) / PI;
}

DMS Utils::degreeToDms(double degree)
{
	int d = floor(degree);
	double m = (degree - d) * 60;
	int s = floor((m - floor(m)) * 60);

	// Flip the sign in the seconds column (from negative to positive) if either degrees or minutes is negative.
	if (d < 0 || m < 0)
	{
		s = abs(s);
	}

	// Flip the sign in the minutes column (from negative to positive) if degrees is negative.
	if (d < 0)
	{
		m = abs(m);
	}

	return DMS(d, floor(m), s);
}

// calculating obliquity of ecliptic(with respect to the mean equator od date) for a given julian day.
// IAU 1976, good from 1000-3000 AD
double Utils::obliquity(const DateTime &dateTime)
{
	double T = (dateTime.getJulianTime() - 2451545.0) / 36525;
	double obl = (23.439291 - 0.0130042 * T - 0.00000016 * T * T + 0.000000504 * T * T * T) / RADIAN;
	return obl;
}

// Local Sidereal Time, (mean or apparent), for vector of JD's and a given East Longitude(In radians).
double Utils::lst(const DateTime &dateTime, double eastLong, bool calcNutation)
{
	// convert JD to integer day + fraction of day
	double TJD = floor(dateTime.getJulianTime() - 0.5) + 0.5;
	double DayFrac = dateTime.getJulianTime() - TJD;

	double T = (TJD - 2451545.0) / 36525.0;

	double GMST0UT = 24110.54841 + 8640184.812866 * T + 0.093104 * T * T - 6.2e-6 * T * T * T;

	// convert to fraction of day in range[0 1)
	GMST0UT = GMST0UT / 86400.0;

	GMST0UT = GMST0UT - floor(GMST0UT);
	double LST = GMST0UT + 1.0027379093 * DayFrac + eastLong / (2.0 * PI);
	LST = LST - floor(LST);

	if (calcNutation)
	{
		// calculate nutation
		double lonNutation = nutation(dateTime);
		double obl = Utils::obliquity(dateTime);
		double EquationOfEquinox = (RADIAN * 3600) * lonNutation * cos(obl) / 15;
		LST = LST + EquationOfEquinox / 86400;
	}

	return LST;
}

// Calculate the Nutation in longitude
double Utils::nutation(const DateTime &dateTime)
{
	double T = (dateTime.getJulianTime() - 2451545.0) / 36525.0;

	// Mean elongation of the Moon from the Sun :
	double D = (297.85036 + 445267.111480 * T - 0.0019142 * T * T + T * T * T / 189474) / RADIAN;

	// Mean anomaly of the Sun(Earth) :
	double M = (357.52772 + 35999.050340 * T - 0.0001603 * T * T - T * T * T / 300000) / RADIAN;

	// Mean anomaly of the Moon :
	double Mt = (134.96298 + 477198.867398 * T + 0.0086972 * T * T + T * T * T / 56250) / RADIAN;

	// Moon's argument of latitude
	double F = (93.27191 + 483202.017538 * T - 0.0036825 * T * T + T * T * T / 327270) / RADIAN;

	// Longitude of ascending node of the Moon's mean orbit
	double Om = (125.04452 - 1934.136261 * T + 0.0020708 * T * T + T * T * T / 450000) / RADIAN;

	// nutation in longitude[0."0001]
	double DLon = (-171996 - 174.2 * T) * sin(Om) +
				  (-13187 + 1.6 * T) * sin(2.0 * (-D + F + Om)) +
				  (-2274 - 0.2 * T) * sin(2.0 * (F + Om)) +
				  (2062 + 0.2 * T) * sin(2.0 * Om) +
				  (1426 - 3.4 * T) * sin(M) +
				  (712 + 0.1 * T) * sin(Mt) +
				  (-517 + 1.2 * T) * sin(2.0 * (-D + F + Om) + M) +
				  (-386 - 0.4 * T) * sin(2.0 * F + Om) +
				  (-301) * sin(Mt + 2 * (F + Om)) +
				  (217 - 0.5 * T) * sin(-M + 2.0 * (-D + F + Om)) +
				  (-158) * sin(-2.0 * D + Mt) +
				  (129 + 0.1 * T) * sin(2.0 * (-D + F) + Om) +
				  (123) * sin(-Mt + 2.0 * (F + Om)) +
				  (63) * sin(2.0 * D) +
				  (63 + 0.1 * T) * sin(Mt + Om) +
				  (-59) * sin(-Mt + 2.0 * (D + F + Om)) +
				  (-58 - 0.1 * T) * sin(-Mt + Om) +
				  (-51) * sin(Mt + 2.0 * F + Om) +
				  (48) * sin(2.0 * (-D + Mt)) +
				  (46) * sin(Om + 2.0 * (-Mt + F)) +
				  (-38) * sin(2.0 * (D + F + Om)) +
				  (-31) * sin(2.0 * (Mt + F + Om)) +
				  (29) * sin(2.0 * Mt) +
				  (29) * sin(Mt + 2.0 * (-D + F + Om)) +
				  (26) * sin(2.0 * F) +
				  (-22) * sin(2.0 * (-D + F)) +
				  (21) * sin(-Mt + Om + 2.0 * F) +
				  (17 - 0.1 * T) * sin(2.0 * M) +
				  (16) * sin(2.0 * D - Mt + Om) +
				  (-16 + 0.1 * T) * sin(2.0 * (-D + M + F + Om)) +
				  (-15) * sin(M + Om) +
				  (-13) * sin(-2.0 * D + Mt + Om) +
				  (-12) * sin(-M + Om) +
				  (11) * sin(2.0 * (Mt - F)) +
				  (-10) * sin(2.0 * (D + F) - Mt + Om) +
				  (-8) * sin(2.0 * (D + F + Om) + Mt) +
				  (7) * sin(2.0 * (F + Om) + M) +
				  (-7) * sin(-2.0 * D + M + Mt) +
				  (-7) * sin(-M + 2. * (F + Om)) +
				  (-7) * sin(2.0 * (D + F) + Om) +
				  (6) * sin(2.0 * D + Mt) +
				  (6) * sin(2.0 * (-D + Mt + F + Om)) +
				  (6) * sin(2.0 * (-D + F) + Mt + Om) +
				  (-6) * sin(2.0 * (D - Mt) + Om) +
				  (-6) * sin(2.0 * D + Om) +
				  (5) * sin(-M + Mt) +
				  (-5) * sin(2.0 * (F - D) + Om - M) +
				  (-5) * sin(Om - 2.0 * D) +
				  (-5) * sin(2.0 * (Mt + F) + Om) +
				  (4) * sin(2.0 * (Mt - D) + Om) +
				  (4) * sin(2.0 * (F - D) + M + Om) +
				  (4) * sin(Mt - 2.0 * F) +
				  (-4) * sin(Mt - D) +
				  (-4) * sin(M - 2.0 * D) +
				  (-4) * sin(D) +
				  (3) * sin(Mt + 2.0 * F) +
				  (-3) * sin(2.0 * (F + Om - Mt)) +
				  (-3) * sin(Mt - D - M) +
				  (-3) * sin(M + Mt) +
				  (-3) * sin(Mt - M + 2.0 * (F - Om)) +
				  (-3) * sin(2.0 * (D + F + Om) - M - Mt) +
				  (-3) * sin(3.0 * Mt + 2.0 * (F + Om)) +
				  (-3) * sin(2.0 * (D + F + Om) - M);

	// convert to radians
	DLon = DLon * 0.0001 / (3600 * RADIAN);

	return DLon;
}

SunCoordinates Utils::suncoo(const DateTime &dateTime)
{
	double julianTime = dateTime.getJulianTime();

	double T = (julianTime - 2451545.0) / 36525;
	double L0 = (280.46645 + 36000.76983 * T + 0.0003032 * T * T) / RADIAN;
	double M = (357.52910 + 35999.05030 * T - 0.0001559 * T * T - 0.00000048 * T * T * T) / RADIAN;

	double C = (1.914600 - 0.004817 * T - 0.000014 * T * T) * sin(M) + (0.019993 - 0.000101 * T) * sin(2.0 * M) + 0.000290 * sin(3.0 * M);
	C = C / RADIAN;

	// Sun longitude
	double SL = L0 + C;

	//the sun radius vector
	//double R = 1.000001018*(1 - e*e) / (1 + e*cos(Ni));

	double Om = (125.04 - 1934.136 * T) / RADIAN;
	SL = SL - (0.00569 - 0.00478 * sin(Om)) / RADIAN;

	double Obl = Utils::obliquity(dateTime);

	SL = (SL / (2 * PI) - floor(SL / (2 * PI))) * 2 * PI;
	double RA = atan2(cos(Obl) * sin(SL), cos(SL));
	double Dec = asin(sin(Obl) * sin(SL));

	return SunCoordinates(RA, Dec);
}
} // namespace sunmoon
