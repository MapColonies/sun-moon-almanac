#include "InterpolationCalculator.h"
#include <limits>
#include <cmath>

using namespace std;

namespace sunmoon
{
int nearestNeighborIndex(vector<double> &x, double &value)
{
	double dist = numeric_limits<double>::max();
	double newDist = dist;
	size_t idx = 0;

	for (size_t i = 0; i < x.size(); ++i)
	{
		newDist = abs(value - x[i]);

		if (newDist <= dist)
		{
			dist = newDist;
			idx = i;
		}
	}

	return idx;
}

vector<double> InterpolationCalculator::interp1(vector<double> &x, vector<double> &y, vector<double> &x_new)
{
	vector<double> y_new;
	double dx, dy, m, b;
	size_t x_max_idx = x.size() - 1;
	size_t x_new_size = x_new.size();

	y_new.reserve(x_new_size);

	for (size_t i = 0; i < x_new_size; ++i)
	{
		size_t idx = nearestNeighborIndex(x, x_new[i]);

		if (x[idx] > x_new[i])
		{
			dx = idx > 0 ? (x[idx] - x[idx - 1]) : (x[idx + 1] - x[idx]);
			dy = idx > 0 ? (y[idx] - y[idx - 1]) : (y[idx + 1] - y[idx]);
		}
		else
		{
			dx = idx < x_max_idx ? (x[idx + 1] - x[idx]) : (x[idx] - x[idx - 1]);
			dy = idx < x_max_idx ? (y[idx + 1] - y[idx]) : (y[idx] - y[idx - 1]);
		}

		m = dy / dx;
		b = y[idx] - x[idx] * m;
		y_new.push_back(x_new[i] * m + b);
	}

	return y_new;
}
} // namespace sunmoon