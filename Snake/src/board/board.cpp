#include "board.hpp"

namespace board
{
	Board::Board() : board(new BoardComponent**[SIZE])
	{
		for (int i = 0; i < SIZE; ++i)
			this->board[i] = new BoardComponent*[SIZE];
	}

	Board::~Board()
	{
		for (int i = 0; i < SIZE; ++i)
			delete this->board[i];
		delete[] this->board;
	}
}
