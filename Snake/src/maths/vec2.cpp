#include "vec2.hpp"

namespace maths {

	vec2::vec2() : vec2(0, 0) { }
	vec2::vec2(const int x, const int y) : m_pos_x_(x), m_pos_y_(y) { }

	vec2& vec2::add(const vec2& other)
	{
		this->m_pos_x_ += other.m_pos_x_;
		this->m_pos_y_ += other.m_pos_y_;
		return *this;
	}

	vec2& vec2::substract(const vec2& other)
	{
		this->m_pos_x_ -= other.m_pos_x_;
		this->m_pos_y_ -= other.m_pos_y_;
		return *this;
	}

	vec2& vec2::multiply(const vec2& other)
	{
		this->m_pos_x_ *= other.m_pos_x_;
		this->m_pos_y_ *= other.m_pos_y_;
		return *this;
	}

	vec2& vec2::divide(const vec2& other)
	{
		this->m_pos_x_ /= other.m_pos_x_;
		this->m_pos_y_ /= other.m_pos_y_;
		return *this;
	}

	bool vec2::operator==(const vec2& pos) const
	{
		return (this->m_pos_x_ == pos.m_pos_x_ && this->m_pos_y_ == pos.m_pos_y_);
	}

	bool vec2::operator!=(const vec2& pos) const
	{
		return !(*this == pos);
	}

	vec2& vec2::operator+=(const vec2& pos)
	{
		return this->add(pos);
	}

	vec2& vec2::operator-=(const vec2& pos)
	{
		return this->substract(pos);
	}

	vec2& vec2::operator*=(const vec2& pos)
	{
		return this->multiply(pos);
	}

	vec2& vec2::operator/=(const vec2& pos)
	{
		return this->divide(pos);
	}

	vec2 operator+(vec2 a, const vec2& b)
	{
		return a.add(b);
	}

	vec2 operator-(vec2 a, const vec2& b)
	{
		return a.substract(b);
	}

	vec2 operator*(vec2 a, const vec2& b)
	{
		return a.multiply(b);
	}

	vec2 operator/(vec2 a, const vec2& b)
	{
		return a.divide(b);
	}
}
