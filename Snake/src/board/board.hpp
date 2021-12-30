#pragma once

#include "boardComponent.hpp"

#include "../snake/snake.hpp"

namespace board
{
	class Board
	{
	public:
		constexpr static int SIZE = 20;

	private:
		BoardComponent*** board;

	public:
		Board();
		~Board();

		inline BoardComponent* getBoardComponent(const int x, const int y) const { return this->board[y][x]; }

		bool updateSnakePositions(const snake::Snake* snake) const;
	};
}