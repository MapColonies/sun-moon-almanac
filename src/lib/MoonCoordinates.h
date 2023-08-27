#pragma once

namespace sunmoon
{
class MoonCoordinates
{
  private:
	double moonRA;  // RA, in radians
	double moonDec; //Dec. in radians
	double moonHP;  // Horizontal parallax. r = 1 / sin(HP)  SD = 0.2725.*HP

  public:
	MoonCoordinates(double ra, double dec, double hp);
	double getMoonRA() const;
	double getMoonDec() const;
	double getMoonHP() const;
};
} // namespace sunmoon
