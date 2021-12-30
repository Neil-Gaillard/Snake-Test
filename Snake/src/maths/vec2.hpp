#pragma once

namespace maths {

	struct vec2
	{
	private:
		int m_pos_x_;
		int m_pos_y_;

	public:
		vec2();
		vec2(int x, int y);

		inline int get_x_pos() const { return this->m_pos_x_; }
		inline int get_y_pos() const { return this->m_pos_y_; }

		inline void set_x_pos(const int x) { this->m_pos_x_ = x; }
		inline void set_y_pos(const int y) { this->m_pos_y_ = y; }

		friend vec2 operator+(vec2 a, const vec2& b);
		friend vec2 operator-(vec2 a, const vec2& b);
		friend vec2 operator*(vec2 a, const vec2& b);
		friend vec2 operator/(vec2 a, const vec2& b);

		bool operator==(const vec2& pos) const;
		bool operator!=(const vec2& pos) const;

		vec2& operator+=(const vec2& pos);
		vec2& operator-=(const vec2& pos);
		vec2& operator*=(const vec2& pos);
		vec2& operator/=(const vec2& pos);

	private:
		vec2& add(const vec2& other);
		vec2& substract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);
	};

}