#pragma once

namespace sunmoon
{
class SunCoordinatesMotion
{
  private:
	double angleRADayM1;
	double angleDecDayM1;
	double angleRADay0;
	double angleDecDay0;
	double angleRADayP1;
	double angleDecDayP1;

  public:
	SunCoordinatesMotion(double raDayM1, double decDayM1, double raDay0, double decDay0, double raDayP1, double decDayP1);
	double getAngleRADayM1() const;
	double getAngleDecDayM1() const;
	double getAngleRADay0() const;
	double getAngleDecDay0() const;
	double getAngleRADayP1() const;
	double getAngleDecDayP1() const;

	void setAngleRADayM1(double value);
	void setAngleRADay0(double value);
	void setAngleRADayP1(double value);
};
} // namespace sunmoon
