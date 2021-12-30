#include "snake.hpp"

namespace snake
{
	Snake::Snake() : m_current_position(10, 10), m_size(4), m_direction(direction::Direction::RIGHT)
	{
		for (int i = 0; i < 3; ++i)
			this->m_previous_positions.push_back(maths::vec2(9 - i, 10));
	}

	void Snake::move(const direction::Direction direction)
	{
		for (auto& m_previous_position : this->m_previous_positions)
			m_previous_position += maths::vec2(1, 0);
	}
}
