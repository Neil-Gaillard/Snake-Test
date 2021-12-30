#include <cstring>
#include <thread>
#include <vector>
#include <Windows.h>

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "board/board.hpp"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define WINDOW_TITLE "Snake"

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

#define COLOR_MATRIX "given_color"

#define INITIAL_X_POSITION 10
#define INITIAL_Y_POSITION 10
#define INITIAL_SIZE 9

void initiate_vbo();

void update_window(const board::Board* board, const graphics::Window* window, const graphics::Shader* shader);

void move_snake(snake::Snake* snake, const board::Board* board);

int main()
{
	const auto* window = new graphics::Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	const auto* shader = new graphics::Shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	shader->enable();

	const auto* board = new board::Board();
	auto* snake = new snake::Snake(maths::vec2(INITIAL_X_POSITION, INITIAL_Y_POSITION), INITIAL_SIZE);

	initiate_vbo();

	std::thread moveSnakeThread(move_snake, snake, board);

	while (!window->closed())
	{
		if (window->isKeyPressed(GLFW_KEY_UP) && snake->getDirection() != direction::Direction::UP && snake->getDirection() != direction::Direction::DOWN)
			snake->setDirection(direction::Direction::UP);
		else if (window->isKeyPressed(GLFW_KEY_DOWN) && snake->getDirection() != direction::Direction::DOWN && snake->getDirection() != direction::Direction::UP)
			snake->setDirection(direction::Direction::DOWN);
		else if (window->isKeyPressed(GLFW_KEY_RIGHT) && snake->getDirection() != direction::Direction::RIGHT && snake->getDirection() != direction::Direction::LEFT)
			snake->setDirection(direction::Direction::RIGHT);
		else if (window->isKeyPressed(GLFW_KEY_LEFT) && snake->getDirection() != direction::Direction::LEFT && snake->getDirection() != direction::Direction::RIGHT)
			snake->setDirection(direction::Direction::LEFT);
		update_window(board, window, shader);
	}
	moveSnakeThread.detach();
	return 0;
}

void initiate_vbo()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);
}

void update_window(const board::Board* board, const graphics::Window* window, const graphics::Shader* shader)
{
	graphics::Window::clear();
	//TODO maybe research a little bite more opengl in order to have something better? 
	for (int i = 0; i < board::Board::SIZE; i++) {
		for (int j = 0; j < board::Board::SIZE; j++) {
			if (board->getBoardComponent(j, i)->isActive()) {
				GLfloat vertices[board::BoardComponent::NUMBER_VERTICES];
				memcpy(vertices, board->getBoardComponent(j, i)->getVertices(), board::BoardComponent::NUMBER_VERTICES * sizeof(GLfloat));
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				shader->setUniform4f(COLOR_MATRIX, board->getBoardComponent(j, i)->getColor());
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}
	window->update();
}

void move_snake(snake::Snake* snake, const board::Board* board)
{
	while (snake->move() && board->updateSnakePositions(snake))
		Sleep(200);
}