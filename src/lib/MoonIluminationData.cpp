#include "MoonIluminationData.h"

using namespace std;

namespace sunmoon
{
MoonIluminationData::MoonIluminationData(double moonAz, double moonEl, double moonIlum, double moonIlumPerc) : moonAzimuth(moonAz), moonElevation(moonEl), moonIluminationLux(moonIlum), moonIluminationPercentage(moonIlumPerc)
{
}

double MoonIluminationData::getMoonAzimuth() const
{
	return moonAzimuth;
}

double MoonIluminationData::getMoonElevation() const
{
	return moonElevation;
}

double MoonIluminationData::getMoonIluminationLux() const
{
	return moonIluminationLux;
}

double MoonIluminationData::getMoonIluminationPercentage() const
{
	return moonIluminationPercentage;
}

std::string MoonIluminationData::toString() const
{
	return "Moon Ilumination Data\n"
		   "Azimuth: " +
		   to_string(moonAzimuth) + ", Elevation: " + to_string(moonElevation) +
		   "\nIlumination: " + to_string(moonIluminationLux) + "LUX (" + to_string(moonIluminationPercentage) + "%)";
}
} // namespace sunmoon
