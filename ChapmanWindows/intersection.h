#pragma once

#include "intersectable.h"

class intersection
{
public:
	intersection(double distance, std::shared_ptr<intersectable> object);
	auto distance() const -> double;
	auto object() const->std::shared_ptr<intersectable>;

private:
	double _distance;
	std::shared_ptr<intersectable> _object;
};

