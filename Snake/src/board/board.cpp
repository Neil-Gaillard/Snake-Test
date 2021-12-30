#include "board.hpp"

namespace board
{
	Board::Board() : board(new BoardComponent**[SIZE])
	{
		for (int i = 0; i < SIZE; ++i) {
			this->board[i] = new BoardComponent * [SIZE];
			for (int j = 0; j < SIZE; ++j)
				this->board[i][j] = new BoardComponent(maths::vec2(j, i), maths::vec4(0.5f, 0.5f, 0.5F, 1.0f));
		}
	}

	Board::~Board()
	{
		for (int i = 0; i < SIZE; ++i)
			delete this->board[i];
		delete[] this->board;
	}

	void Board::updateSnakePositions(const snake::Snake* snake) const
	{
		for (int i = 0 ; i < snake->getSize() - 1; ++i )
			this->board[snake->getPreviousPositions(i).get_x_pos()][snake->getPreviousPositions(i).get_y_pos()]->setActive(true);
		this->board[snake->getCurrentPosition().get_x_pos()][snake->getCurrentPosition().get_y_pos()]->setActive(true);
	}
}
