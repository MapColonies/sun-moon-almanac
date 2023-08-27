#pragma once
#include <vector>

namespace sunmoon
{
class InterpolationCalculator
{
  public:
	std::vector<double> interp1(std::vector<double> &x, std::vector<double> &y, std::vector<double> &x_new);
};
} // namespace sunmoon