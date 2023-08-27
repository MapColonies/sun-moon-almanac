#include "MoonIluminationCalculator.h"
#include "MoonCoordinates.h"
#include "Utils.h"
#include <math.h>

namespace sunmoon
{
MoonIluminationData MoonIluminationCalculator::calculate(const Location &location, const DateTime &dateTime)
{
	double FM_LUX_UNIT = 0.27; //lx

	MoonCoordinates moonCoordinates = getMoonCoordinates(location, dateTime);
	SunCoordinates sunCoordinates = Utils::suncoo(dateTime);

	// Calculate Moon Elongation
	double moonElongation = acos(sin(moonCoordinates.getMoonDec()) * sin(sunCoordinates.getAngleDec()) +
								 cos(moonCoordinates.getMoonDec()) * cos(sunCoordinates.getAngleDec()) * cos(moonCoordinates.getMoonRA() - sunCoordinates.getAngleRA()));

	double horizAz;
	double horizAlt;
	calcHorizontalCoordinates(moonCoordinates, dateTime, location, horizAz, horizAlt);
	double moonAz = horizAz;
	double moonEl = horizAlt;

	// Calculate moon illumination in flux
	double moonIluminationLUX = calcMoonLight(horizAlt, moonCoordinates.getMoonHP(), moonElongation);

	// full moon percentage - normalization - could provide 100 + % -should be with if to lower to 100 %
	double moonIluminationRatio = (moonIluminationLUX / FM_LUX_UNIT);

	if (moonIluminationRatio > 1)
	{
		moonIluminationRatio = 1;
	}

	return MoonIluminationData(Utils::radToDegree(moonAz), Utils::radToDegree(moonEl), moonIluminationLUX, round(moonIluminationRatio * 100));
}

MoonCoordinates MoonIluminationCalculator::getMoonCoordinates(const Location &location, const DateTime &dateTime)
{
	double Lon, Lat, HP;
	monecool(dateTime, Lon, Lat, HP);

	double R = 1.0 / sin(HP);

	double Obl = Utils::obliquity(dateTime);

	double L = cos(Lat) * cos(Lon);
	double M = cos(Obl) * cos(Lat) * sin(Lon) - sin(Obl) * sin(Lat);
	double N = sin(Obl) * cos(Lat) * sin(Lon) + cos(Obl) * sin(Lat);

	double x = R * L;
	double y = R * M;
	double z = R * N;

	double xt, yt, zt;

	if (isnan(location.getLatRadians()) || isnan(location.getLonRadians()))
	{
		// geocentric coordinates
		xt = x;
		yt = y;
		zt = z;
	}
	else
	{
		double LST = Utils::lst(dateTime.getJulianTime(), location.getLatRadians(), false) * 2 * PI;
		Lat = location.getLonRadians();

		xt = x - cos(Lat) * cos(LST);
		yt = y - cos(Lat) * sin(LST);
		zt = z - sin(Lat);
	}

	double RA = atan2(yt, xt);
	double Dec = asin(zt / sqrt(xt * xt + yt * yt + zt * zt));

	return MoonCoordinates(RA, Dec, HP);
}

double funTPI(double x)
{
	return (x / (2 * PI) - floor(x / (2 * PI))) * 2 * PI;
}

void MoonIluminationCalculator::monecool(const DateTime &dateTime, double &lon, double &lat, double &hp)
{
	double T = (dateTime.getJulianTime() - 2451545) / 36525.0;

	// Moon's mean longitude (equinox of date + light term)
	double Lt = 218.3164591 + 481267.88134236 * T - 0.0013268 * T * T + T * T * T / 538841 - T * T * T * T / 65194000;

	// Mean elongation of the Moon
	double D = 297.8502042 + 445267.1115168 * T - 0.0016300 * T * T + T * T * T / 545868 - T * T * T * T / 113065000;

	// Sun's mean anomaly
	double M = 357.5291092 + 35999.0502909 * T - 0.0001536 * T * T + T * T * T / 24490000;

	// Moon's mean anomaly
	double Mt = 134.9634114 + 477198.8676313 * T + 0.0089970 * T * T + T * T * T / 69699 + T * T * T * T / 14712000;

	// Moon's argument of latitude
	double F = 93.2720993 + 483202.0175273 * T - 0.0034029 * T * T - T * T * T / 3526000 + T * T * T * T / 863310000;

	// Earth eccentricity
	double E = 1 - 0.002516 * T - 0.0000074 * T * T;

	// convert to radians
	Lt = Lt / RADIAN;
	D = D / RADIAN;
	M = M / RADIAN;
	Mt = Mt / RADIAN;
	F = F / RADIAN;

	// convert to 0 - 2\pi
	Lt = funTPI(Lt);
	D = funTPI(D);
	M = funTPI(M);
	Mt = funTPI(Mt);
	F = funTPI(F);

	double SumL = 6288774. * sin(Mt) +
				  1274027. * sin(2. * D - Mt) +
				  658314. * sin(2. * D) +
				  213618. * sin(2. * Mt) -
				  185116. * sin(M) * E -
				  114332. * sin(2. * F) +
				  58793. * sin(2. * D - 2. * Mt) +
				  57066. * sin(2. * D - M - Mt) * E +
				  53322. * sin(2. * D + Mt) +
				  45758. * sin(2. * D - M) * E -
				  40923. * sin(M - Mt) * E -
				  34720. * sin(D) -
				  30383. * sin(M + Mt) * E +
				  15327. * sin(2. * D - 2. * F) -
				  12528. * sin(Mt + 2. * F) +
				  10980. * sin(Mt - 2. * F) +
				  10675. * sin(4. * D - Mt) +
				  10034. * sin(Mt) +
				  8548. * sin(4. * D - 2. * Mt) -
				  7888. * sin(2. * D + M - Mt) * E -
				  6766. * sin(2. * D + M) * E -
				  5163. * sin(D - Mt);

	double SumR = -20905355. * cos(Mt) - 3699111. * cos(2. * D - Mt) - 2955968. * cos(2. * D) - 569925. * cos(2. * Mt) + 48888. * cos(M) * E - 3149. * cos(2. * F) + 246158. * cos(2. * D - 2. * Mt) - 152138. * cos(2. * D - M - Mt) * E - 170733. * cos(2. * D + Mt) - 204586. * cos(2. * D - M) * E - 129620. * cos(M - Mt) * E + 108743. * cos(D) + 104755. * cos(M + Mt) * E + 10321. * cos(2. * D - 2. * F) + 0. * cos(Mt + 2. * F) + 79661. * cos(Mt - 2. * F) - 34782. * cos(4. * D - Mt) - 23210. * cos(Mt) - 21636. * cos(4. * D - 2. * Mt) + 24208. * cos(2. * D + M - Mt) * E + 30824. * cos(2. * D + M) * E - 8379. * cos(D - Mt);

	double SumB = 5128122. * sin(F) + 280602. * sin(Mt + F) + 277693. * sin(Mt - F) + 173237. * sin(2. * D - F) + 55413. * sin(2. * D - Mt + F) + 46271. * sin(2. * D - Mt - F) + 32573. * sin(2. * D + F) + 17198. * sin(2. * Mt + F) + 9266. * sin(2. * D + Mt - F) + 8822. * sin(2. * Mt - F) + 8216. * sin(2. * D - M - F) * E;

	lon = Lt + SumL * 1e-6 / RADIAN;
	lat = SumB * 1e-6 / RADIAN;
	double Rad = 385000.56 + SumR * 1e-3;
	hp = asin(6378.14 / Rad);
}

// Horizontal coordinates conversion. Converting from equatorial coordinates to Horizontal coordinates and visa versa
void MoonIluminationCalculator::calcHorizontalCoordinates(const MoonCoordinates &moonCoordinates, const DateTime &dateTime, const Location &location, double &horizAz, double &horizAlt)
{
	double LST = Utils::lst(dateTime.getJulianTime(), location.getLonRadians(), false);

	// calculate the Hour Angle
	double HA = LST * 2 * PI - moonCoordinates.getMoonRA();
	double Dec = moonCoordinates.getMoonDec();
	double Lat = location.getLatRadians();

	double SinAlt = sin(Dec) * sin(Lat) + cos(Dec) * cos(HA) * cos(Lat);
	double CosAlt = sqrt(1 - SinAlt * SinAlt);

	double SinAz = (-cos(Dec) * sin(HA)) / CosAlt;
	double CosAz = (sin(Dec) * cos(Lat) - cos(Dec) * cos(HA) * sin(Lat)) / CosAlt;

	horizAz = atan2(SinAz, CosAz);
	horizAlt = asin(SinAlt);

	if (horizAz < 0)
	{
		horizAz = horizAz + 2 * PI;
	}
}

//calculate the Moon illumination in Lux on horizontal surface as function as its altitude, horizontal parallax and Elongation. in radians.
double MoonIluminationCalculator::calcMoonLight(double moonAlt, double moonHP, double moonElon)
{
	double X = moonAlt * RADIAN / 90;

	double LI1;

	// Handle Altitude
	if (moonAlt * RADIAN > 20)
	{
		double L0 = -1.95;
		double L1 = 4.06;
		double L2 = -4.24;
		double L3 = 1.56;
		LI1 = L0 + L1 * X + L2 * X * X + L3 * X * X * X;
	}
	else if ((moonAlt * RADIAN <= 20) && (moonAlt * RADIAN > 5))
	{
		double L0 = -2.58;
		double L1 = 12.58;
		double L2 = -42.58;
		double L3 = 59.06;
		LI1 = L0 + L1 * X + L2 * X * X + L3 * X * X * X;
	}
	else if ((moonAlt * RADIAN <= 5) && (moonAlt * RADIAN > -0.8))
	{
		double L0 = -2.79;
		double L1 = 24.27;
		double L2 = -252.95;
		double L3 = 1321.29;
		LI1 = L0 + L1 * X + L2 * X * X + L3 * X * X * X;
	}
	else
	{
		// no light
		LI1 = -10;
	}

	// Handle Elongation
	double f = 180 - moonElon * RADIAN;
	double LI2 = -8.68e-3 * f - 2.2e-9 * f * f * f * f;

	// Handle Parallax
	double LI3 = 2. * log10(moonHP * RADIAN / 0.951);

	double Illum = pow(10, (LI1 + LI2 + LI3));

	return Illum;
}
} // namespace sunmoon
