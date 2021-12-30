#include "snake.hpp"

#include "../board/board.hpp"

namespace snake
{
	Snake::Snake() : m_current_position(10, 10), m_size(4), m_direction(direction::Direction::RIGHT)
	{
		for (int i = 0; i < 3; ++i)
			this->m_previous_positions.push_back(maths::vec2(9 - i, 10));
	}

	bool Snake::move()
	{
		maths::vec2 newPos;
		switch (this->m_direction)
		{
		case direction::Direction::UP:
			newPos = maths::vec2(0, -1);
			break;
		case direction::Direction::DOWN:
			newPos = maths::vec2(0, 1);
			break;
		case direction::Direction::LEFT:
			newPos = maths::vec2(-1, 0);
			break;
		case direction::Direction::RIGHT:
			newPos = maths::vec2(1, 0);
		}
		newPos += this->m_current_position;
		
		if (newPos.get_x_pos() < 0 || newPos.get_x_pos() >= board::Board::SIZE ||
			newPos.get_y_pos() < 0 || newPos.get_y_pos() >= board::Board::SIZE)
			return false;

		this->m_previous_positions.push_back(this->getCurrentPosition());
		this->m_current_position = newPos;
		this->m_previous_positions.pop_back();

		return true;
	}
}
