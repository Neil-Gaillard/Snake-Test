#include "board.hpp"

#include <random>

namespace board
{
	Board::Board() : board(new BoardComponent**[SIZE])
	{
		for (int i = 0; i < SIZE; ++i) {
			this->board[i] = new BoardComponent * [SIZE];
			for (int j = 0; j < SIZE; ++j)
				this->board[i][j] = new BoardComponent(maths::vec2(i, j), maths::vec4(0.8f, 0.8f, 0.8F, 1.0f));
		}
	}

	Board::~Board()
	{
		for (int i = 0; i < SIZE; ++i)
			delete this->board[i];
		delete[] this->board;
	}

	bool Board::updateSnakePositions(snake::Snake* snake) const
	{
		if (this->board[snake->getCurrentPosition().get_y_pos()][snake->getCurrentPosition().get_x_pos()]->isApple()) {
			this->board[snake->getCurrentPosition().get_y_pos()][snake->getCurrentPosition().get_x_pos()]->setApple(false);
			snake->makeBigger();
			this->createApple();
		}

		this->board[snake->getLastDeletedPosition().get_y_pos()][snake->getLastDeletedPosition().get_x_pos()]->setActive(false);
		if (this->board[snake->getCurrentPosition().get_y_pos()][snake->getCurrentPosition().get_x_pos()]->isActive()) {
			this->board[snake->getLastDeletedPosition().get_y_pos()][snake->getLastDeletedPosition().get_x_pos()]->setActive(true);
			return false;
		}
		
		for (int i = 0; i < snake->getSize() - 1; ++i) {
			this->board[snake->getPreviousPositions(i).get_y_pos()][snake->getPreviousPositions(i).get_x_pos()]->setActive(true);
			this->board[snake->getPreviousPositions(i).get_y_pos()][snake->getPreviousPositions(i).get_x_pos()]->setColor(maths::vec4(0.8f, 0.8f, 0.8f, 1.0f));
		}
		this->board[snake->getCurrentPosition().get_y_pos()][snake->getCurrentPosition().get_x_pos()]->setActive(true);
		this->board[snake->getCurrentPosition().get_y_pos()][snake->getCurrentPosition().get_x_pos()]->setColor(maths::vec4(0.9f, 0.0f, 0.0f, 1.0f));
		return true;
	}

	void Board::createApple() const
	{
		int posX, posY;

		do {
			posX = rand() % SIZE;
			posY = rand() % SIZE;
		} while (this->board[posY][posX]->isActive());

		this->board[posY][posX]->setApple(true);
		this->board[posY][posX]->setColor(maths::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}