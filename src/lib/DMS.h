#pragma once
#include <string>

// D = Hours, M = minutes, S = seconds
namespace sunmoon
{
class DMS
{
  private:
	int degrees;
	int minutes;
	int seconds;

  public:
	DMS(int d, int m, int s);
	DMS();
	int getDegrees() const;
	int getMinutes() const;
	int getSeconds() const;
	std::string toString() const;
};
} // namespace sunmoon