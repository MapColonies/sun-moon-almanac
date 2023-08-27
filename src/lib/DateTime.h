#pragma once

namespace sunmoon
{
	class DateTime
	{
	private:
		double julianTime;
		static int timeZoneDelta;

	public:
		DateTime(int year, int month, int day, int hour, int minute, int second);
		DateTime(double otherJulianTime);
		double getJulianTime() const;
		DateTime addDays(int days) const;
		DateTime minusHours(int hours) const;
		static int getTimeZone();
		static void setTimeZone(int tz);
	};
} // namespace sunmoon
