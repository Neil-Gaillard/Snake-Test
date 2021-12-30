#include "snake.hpp"

#include "../board/board.hpp"

namespace snake
{
	Snake::Snake(const maths::vec2 initialPosition, const int size)
	: m_current_position(initialPosition.get_x_pos(), initialPosition.get_y_pos()), m_size(size), m_direction(direction::Direction::RIGHT)
	{
		this->m_last_deleted_position = maths::vec2(initialPosition.get_x_pos() - this->m_size, initialPosition.get_y_pos());
		for (int i = initialPosition.get_x_pos() - this->m_size + 1; i < initialPosition.get_x_pos(); ++i)
			this->m_previous_positions.insert(this->m_previous_positions.begin(), maths::vec2(i, initialPosition.get_y_pos()));
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

		this->m_previous_positions.insert(this->m_previous_positions.begin(), this->getCurrentPosition());
		this->m_current_position = newPos;
		this->m_last_deleted_position = this->m_previous_positions.back();
		this->m_previous_positions.pop_back();
		return true;
	}

	void Snake::makeBigger()
	{
		this->m_previous_positions.push_back(this->m_last_deleted_position);
		++this->m_size;
	}
}