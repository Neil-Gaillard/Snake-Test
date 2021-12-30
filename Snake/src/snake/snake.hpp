#pragma once

#include <vector>

#include "../maths/vec2.hpp"
#include "../direction/direction.hpp"

namespace snake
{
	class Snake
	{
	private:
		maths::vec2 m_current_position;
		int m_size;
		direction::Direction m_direction;

		std::vector<maths::vec2> m_previous_positions;

	public:
		Snake();

		inline int getSize() const { return this->m_size; }
		inline maths::vec2 getCurrentPosition() const { return this->m_current_position; }
		inline maths::vec2 getPreviousPositions(const int i) const { return this->m_previous_positions.at(i); }
		inline direction::Direction getDirection() const { return this->m_direction; }

		void move(const direction::Direction direction);
	};
}