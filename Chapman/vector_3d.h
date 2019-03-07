#pragma once

class vector3
{
public:
	vector3();
	vector3(double x, double y, double z);
	vector3(vector3& v) = default;
	vector3(vector3&& v) noexcept;
	auto operator=(const vector3& v)->vector3& = default;
	auto operator=(vector3&& v) noexcept->vector3&;
	~vector3() = default;

	auto operator==(const vector3& v) const -> bool;
	auto operator!=(const vector3& v) const -> bool;

	auto operator+(const vector3& v) const->vector3;
	auto operator-(const vector3& v) const->vector3;
	auto operator^(const vector3& v) const->vector3;
	auto operator*(const vector3& v) const -> double;

	auto operator-() const->vector3;

private:
	double _x;
	double _y;
	double _z;
};

