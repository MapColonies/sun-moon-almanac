#pragma once

namespace sunmoon
{
class RiseSetInfo
{
  private:
	double riseAzimuth;
	double setAzimuth;
	double riseTime;
	double setTime;
	double transitTime;

  public:
	double getRiseAzimuth() const;
	double getSetAzimuth() const;
	double getRiseTime() const;
	double getSetTime() const;
	double getTransitTime() const;
	void setRiseTime(double newRiseTime);
	void setTransitTime(double newTransitTime);
	void setSetTime(double newSetTime);
	void setRiseAzimuth(double newRiseAzimuth);
	void setSetAzimuth(double newSetAzimuth);
	void addTimeZone(int timeZone);
};
} // namespace sunmoon
