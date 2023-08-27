#pragma once

namespace sunmoon
{
class SunCoordinates
{
  private:
	double angleRA;
	double angleDec;

  public:
	SunCoordinates(double ra, double dec);
	double getAngleRA() const;
	double getAngleDec() const;
};
} // namespace sunmoon
