#include "SunTwilightsCalculator.h"
#include "Utils.h"
#include "SunCoordinates.h"
#include "SunCoordinatesMotion.h"
#include "RiseSetInfo.h"
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

namespace sunmoon
{
SunTwilightsData SunTwilightsCalculator::calculate(const Location &location, const DateTime &dateTime)
{
	int deltaT = 0;

	double RS_Alt = -0.8333 / RADIAN;
	double T06_Alt = -6 / RADIAN;
	double T12_Alt = -12 / RADIAN;
	double T18_Alt = -18 / RADIAN;

	SunCoordinates sunM2 = Utils::suncoo(dateTime.addDays(-2));
	SunCoordinates sunM1 = Utils::suncoo(dateTime.addDays(-1));
	SunCoordinates sun0 = Utils::suncoo(dateTime);
	SunCoordinates sunP1 = Utils::suncoo(dateTime.addDays(1));
	SunCoordinates sunP2 = Utils::suncoo(dateTime.addDays(2));

	double gast = Utils::lst(dateTime, 0);
	double gastP = Utils::lst(dateTime.addDays(1), 0);
	double gastM = Utils::lst(dateTime.addDays(-1), 0);

	SunCoordinatesMotion motion0(
		sunM1.getAngleRA(),
		sunM1.getAngleDec(),
		sun0.getAngleRA() < sunM1.getAngleRA() ? sun0.getAngleRA() + 2 * PI : sun0.getAngleRA(),
		sun0.getAngleDec(),
		sunP1.getAngleRA() < sun0.getAngleRA() ? sunP1.getAngleRA() + 2 * PI : sunP1.getAngleRA(),
		sunP1.getAngleDec());

	SunCoordinatesMotion motionM(
		sunM2.getAngleRA(),
		sunM2.getAngleDec(),
		sunM1.getAngleRA() < sunM2.getAngleRA() ? sunM1.getAngleRA() + 2 * PI : sunM1.getAngleRA(),
		sunM1.getAngleDec(),
		sun0.getAngleRA() < sunM1.getAngleRA() ? sun0.getAngleRA() + 2 * PI : sun0.getAngleRA(),
		sun0.getAngleDec());

	SunCoordinatesMotion motionP(
		sun0.getAngleRA(),
		sun0.getAngleDec(),
		sunP1.getAngleRA() < sun0.getAngleRA() ? sunP1.getAngleRA() + 2 * PI : sunP1.getAngleRA(),
		sun0.getAngleDec(),
		sunP2.getAngleRA() < sunP1.getAngleRA() ? sunP2.getAngleRA() + 2 * PI : sunP2.getAngleRA(),
		sunP2.getAngleDec());

	SunTwilightsData twilightData;

	// Rise/Set
	RiseSetInfo info = riseSet(motion0, motionP, motionM, gast, gastP, gastM, dateTime.getTimeZone(), RS_Alt, location, deltaT);
	twilightData.setRiseTime(Utils::degreeToDms(info.getRiseTime() * 24));
	twilightData.setSetTime(Utils::degreeToDms(info.getSetTime() * 24));

	// Translate radians to degrees and set
	twilightData.setDawnAzimuth(Utils::radToDegree(info.getRiseAzimuth()));
	twilightData.setDuskAzimuth(Utils::radToDegree(info.getSetAzimuth()));

	// Civil Twilight
	RiseSetInfo info06 = riseSet(motion0, motionP, motionM, gast, gastP, gastM, dateTime.getTimeZone(), T06_Alt, location, deltaT);
	twilightData.setDawnTime06(Utils::degreeToDms(info06.getRiseTime() * 24));
	twilightData.setDuskTime06(Utils::degreeToDms(info06.getSetTime() * 24));

	// Nautical Twilight
	RiseSetInfo info12 = riseSet(motion0, motionP, motionM, gast, gastP, gastM, dateTime.getTimeZone(), T12_Alt, location, deltaT);
	twilightData.setDawnTime12(Utils::degreeToDms(info12.getRiseTime() * 24));
	twilightData.setDuskTime12(Utils::degreeToDms(info12.getSetTime() * 24));

	// Astronomical Twilight
	RiseSetInfo info18 = riseSet(motion0, motionP, motionM, gast, gastP, gastM, dateTime.getTimeZone(), T18_Alt, location, deltaT);
	twilightData.setDawnTime18(Utils::degreeToDms(info18.getRiseTime() * 24));
	twilightData.setDuskTime18(Utils::degreeToDms(info18.getSetTime() * 24));

	return twilightData;
}

RiseSetInfo SunTwilightsCalculator::riseSet(const SunCoordinatesMotion &motion0, const SunCoordinatesMotion &motionP, const SunCoordinatesMotion &motionM, double gast, double gastP, double gastM,
											int timeZone, double altitude, const Location &location, int deltaT)
{
	// Rise/Set
	RiseSetInfo info = riseSet(motion0, gast, altitude, location, deltaT);
	info.addTimeZone(timeZone);

	if (info.getRiseTime() > 1)
	{
		RiseSetInfo infoP = riseSet(motionP, gastP, altitude, location, deltaT);
		info.setRiseTime(infoP.getRiseTime());
		info.setSetAzimuth(infoP.getSetAzimuth());
	}

	if (info.getTransitTime() < 0)
	{
		RiseSetInfo infoM = riseSet(motionM, gastM, altitude, location, deltaT);
		info.setTransitTime(infoM.getTransitTime());
		info.setRiseAzimuth(infoM.getRiseAzimuth());
	}

	return info;
}

// Given an object coordinates and observer position calculate, rise / set / transit times, azimuth and altitude. The times are in the UT1(not UTC) system.
RiseSetInfo SunTwilightsCalculator::riseSet(const SunCoordinatesMotion &motion, double gast, double altitude, const Location &location, int deltaT)
{
	double diffRA1 = motion.getAngleRADay0() - motion.getAngleRADayM1();
	double diffRA2 = motion.getAngleRADayP1() - motion.getAngleRADay0();

	SunCoordinatesMotion motionCopy = motion;

	if (diffRA1 < -PI)
	{
		motionCopy.setAngleRADay0(motionCopy.getAngleDecDay0() + 2.0 * PI);
		motionCopy.setAngleRADayP1(motionCopy.getAngleDecDayP1() + 2.0 * PI);
	}
	else if (diffRA2 < -PI)
	{
		motionCopy.setAngleRADayP1(motionCopy.getAngleDecDayP1() + 2.0 * PI);
	}
	else if (diffRA1 > PI)
	{
		motionCopy.setAngleRADay0(motionCopy.getAngleDecDay0() - 2.0 * PI);
		motionCopy.setAngleRADayP1(motionCopy.getAngleDecDayP1() - 2.0 * PI);
	}
	else if (diffRA2 > PI)
	{
		motionCopy.setAngleRADayP1(motionCopy.getAngleDecDayP1() - 2.0 * PI);
	}

	// Calculate getAngleRADay0 sign
	int signRADay0 = 0;

	if (motionCopy.getAngleRADay0() > 0)
	{
		signRADay0 = 1;
	}

	if (motionCopy.getAngleRADay0() < 0)
	{
		signRADay0 = -1;
	}

	// Patch by Luca Boschini
	if (abs(motionCopy.getAngleRADayM1()) > PI)
	{
		motionCopy.setAngleRADayM1(motionCopy.getAngleRADayM1() + signRADay0 * 2.0 * PI);
	}
	else if (abs(motionCopy.getAngleRADay0() - motionCopy.getAngleRADayP1()) > PI)
	{
		motionCopy.setAngleRADayP1(motionCopy.getAngleRADayP1() + signRADay0 * 2.0 * PI);
	}

	double ObsLon = location.getLonRadians();
	double ObsLat = location.getLatRadians();

	double CosH0 = (sin(altitude) - sin(ObsLat) * sin(motionCopy.getAngleDecDay0())) / (cos(ObsLat) * cos(motionCopy.getAngleDecDay0()));
	double H0 = acos(CosH0);

	double m1 = (motionCopy.getAngleRADay0() - ObsLon - gast * 2.0 * PI) / (2.0 * PI); // for the transit[fraction of day].
	double m2 = m1 - H0 / (2.0 * PI);												   // for rising
	double m3 = m1 + H0 / (2.0 * PI);												   // for setting

	m1 = m1 - floor(m1);
	m2 = m2 - floor(m2);
	m3 = m3 - floor(m3);

	// DelM = ones(3, 1);
	double delM1 = 1;
	double delM2 = 1;
	double delM3 = 1;
	double Accuracy = 0.2 / 1440;

	double Az1 = 0;
	double Az2 = 0;
	double Az3 = 0;

	while (max(max(abs(delM1), abs(delM2)), abs(delM3)) > (Accuracy))
	{
		// sidereal time at Greenwich[fraction of days]:
		double gastT1 = gast + 360.985647 * m1 / 360;
		double gastT2 = gast + 360.985647 * m2 / 360;
		double gastT3 = gast + 360.985647 * m3 / 360;
		gastT1 = gastT1 - floor(gastT1);
		gastT2 = gastT2 - floor(gastT2);
		gastT3 = gastT3 - floor(gastT3);

		// interpolate RA / Dec:
		double n1 = m1 + deltaT;
		double n2 = m2 + deltaT;
		double n3 = m3 + deltaT;

		if (abs(n1) > 1)
		{
			n1 = 0;

			if (n1 > 0)
			{
				n1 = 1;
			}
			else if (n1 < 0)
			{
				n1 = -1;
			}
		}

		if (abs(n2) > 1)
		{
			n2 = 0;

			if (n2 > 0)
			{
				n2 = 1;
			}
			else if (n2 < 0)
			{
				n2 = -1;
			}
		}

		if (abs(n3) > 1)
		{
			n3 = 0;

			if (n3 > 0)
			{
				n3 = 1;
			}
			else if (n3 < 0)
			{
				n3 = -1;
			}
		}

		vector<double> x = {-1, 0, 1};
		vector<double> ra = {motionCopy.getAngleRADayM1(), motionCopy.getAngleRADay0(), motionCopy.getAngleRADayP1()};
		vector<double> dec = {motionCopy.getAngleDecDayM1(), motionCopy.getAngleDecDay0(), motionCopy.getAngleDecDayP1()};
		vector<double> n = {n1, n2, n3};
		vector<double> rat = interp1.interp1(x, ra, n);
		vector<double> dect = interp1.interp1(x, dec, n);
		double RAT1 = rat[0];
		double RAT2 = rat[1];
		double RAT3 = rat[2];
		double DecT1 = dect[0];
		double DecT2 = dect[1];
		double DecT3 = dect[2];

		// local HA of object[radians]
		double H1 = (gastT1 * 2.0 * PI + ObsLon - RAT1) + PI;
		double H2 = (gastT2 * 2.0 * PI + ObsLon - RAT2) + PI;
		double H3 = (gastT3 * 2.0 * PI + ObsLon - RAT3) + PI;

		H1 = ((H1 / (2.0 * PI) - floor(H1 / (2.0 * PI))) * 2.0 * PI) - PI;
		H2 = ((H2 / (2.0 * PI) - floor(H2 / (2.0 * PI))) * 2.0 * PI) - PI;
		H3 = ((H3 / (2.0 * PI) - floor(H3 / (2.0 * PI))) * 2.0 * PI) - PI;

		// object altitude and azimuth[radians]
		double Alt1 = asin(sin(ObsLat) * sin(DecT1) + cos(ObsLat) * cos(DecT1) * cos(H1));
		double Alt2 = asin(sin(ObsLat) * sin(DecT2) + cos(ObsLat) * cos(DecT2) * cos(H2));
		double Alt3 = asin(sin(ObsLat) * sin(DecT3) + cos(ObsLat) * cos(DecT3) * cos(H3));

		double SinAz1 = -cos(DecT1) * sin(H1) / cos(Alt1);
		double SinAz2 = -cos(DecT2) * sin(H2) / cos(Alt2);
		double SinAz3 = -cos(DecT3) * sin(H3) / cos(Alt3);

		double CosAz1 = (sin(DecT1) * cos(ObsLat) - cos(DecT1) * cos(H1) * sin(ObsLat)) / cos(Alt1);
		double CosAz2 = (sin(DecT2) * cos(ObsLat) - cos(DecT2) * cos(H2) * sin(ObsLat)) / cos(Alt2);
		double CosAz3 = (sin(DecT3) * cos(ObsLat) - cos(DecT3) * cos(H3) * sin(ObsLat)) / cos(Alt3);

		Az1 = atan2(SinAz1, CosAz1);
		Az2 = atan2(SinAz2, CosAz2);
		Az3 = atan2(SinAz3, CosAz3);

		// corrections[fraction of day]:
		delM1 = -H1 / (2.0 * PI);
		delM2 = (Alt2 - altitude) / (2.0 * PI * cos(DecT2) * cos(ObsLat) * sin(H2));
		delM3 = (Alt3 - altitude) / (2.0 * PI * cos(DecT3) * cos(ObsLat) * sin(H3));

		m1 = m1 + delM1;
		m2 = m2 + delM2;
		m3 = m3 + delM3;
	}

	if (abs(CosH0) > 1)
	{
		// object is below / above the horizon all the time
		m2 = NAN;
		m3 = NAN;
	}

	if (Az1 < 0)
	{
		Az1 = Az1 + 2 * PI;
	}

	if (Az2 < 0)
	{
		Az2 = Az2 + 2 * PI;
	}

	if (Az3 < 0)
	{
		Az3 = Az3 + 2 * PI;
	}

	RiseSetInfo riseSetInfo;
	riseSetInfo.setRiseAzimuth(Az2);
	riseSetInfo.setSetAzimuth(Az3);
	riseSetInfo.setRiseTime(m2);
	riseSetInfo.setTransitTime(m1);
	riseSetInfo.setSetTime(m3);

	return riseSetInfo;
}
} // namespace sunmoon
