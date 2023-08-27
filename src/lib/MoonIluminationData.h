#pragma once

#include <string>

namespace sunmoon
{
class MoonIluminationData
{
  private:
	double moonAzimuth;
	double moonElevation;
	double moonIluminationLux;
	double moonIluminationPercentage;

  public:
	MoonIluminationData(double moonAz, double moonEl, double moonIlum, double moonIlumPerc);
	std::string toString() const;
	double getMoonAzimuth() const;
	double getMoonElevation() const;
	double getMoonIluminationLux() const;
	double getMoonIluminationPercentage() const;
};
} // namespace sunmoon
