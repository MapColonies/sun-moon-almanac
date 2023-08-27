#pragma once

#include "DMS.h"
#include <string>

namespace sunmoon
{
class SunTwilightsData
{
  private:
	// In degrees
	double dawnAzimuth;
	double duskAzimuth;

	DMS riseTime;
	DMS setTime;

	// x degrees beneath the horizon
	DMS dawnTime06;
	DMS dawnTime12;
	DMS dawnTime18;
	DMS duskTime06;
	DMS duskTime12;
	DMS duskTime18;

  public:
	void setDawnAzimuth(double dawnAzimuthValue);
	void setDuskAzimuth(double duskAzimuthValue);

	void setRiseTime(DMS riseTimeValue);
	void setSetTime(DMS setTimeValue);
	void setDawnTime06(DMS dawnTime06Value);
	void setDawnTime12(DMS dawnTime12Value);
	void setDawnTime18(DMS dawnTime18Value);
	void setDuskTime06(DMS duskTime06Value);
	void setDuskTime12(DMS duskTime12Value);
	void setDuskTime18(DMS duskTime18Value);

	double getDawnAzimuth() const;
	double getDuskAzimuth() const;

	DMS getRiseTime() const;
	DMS getSetTime() const;
	DMS getDawnTime06() const;
	DMS getDawnTime12() const;
	DMS getDawnTime18() const;
	DMS getDuskTime06() const;
	DMS getDuskTime12() const;
	DMS getDuskTime18() const;

	std::string toString() const;
};
} // namespace sunmoon
