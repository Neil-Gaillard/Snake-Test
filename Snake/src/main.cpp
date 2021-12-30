#include <cstring>

#include "graphics/window.hpp"
#include "graphics/shader.hpp"

#include "board/board.hpp"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800
#define WINDOW_TITLE "Snake"

#define VERTEX_SHADER_PATH "src/graphics/shaders/basic.vert"
#define FRAGMENT_SHADER_PATH "src/graphics/shaders/basic.frag"

#define COLOR_MATRIX "given_color"

int main()
{
	const graphics::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	const graphics::Shader shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	shader.enable();

	while (!window.closed())
	{
		graphics::Window::clear();
		window.update();
	}
	return 0;
}

void update_window(const board::Board* board, const graphics::Window* window, const graphics::Shader* shader)
{
	graphics::Window::clear();
	int k = 0;
	for (int i = 0; i < board::Board::SIZE; i++) {
		for (int j = 0; j < board::Board::SIZE; j++) {
			if (board->getBlockComponent(j, i)->isActive()) {
				GLfloat vertices[board::Board::SIZE * board::Board::SIZE][board::BoardComponent::NUMBER_VERTICES];
				memcpy(vertices[k], board->getBlockComponent(j, i)->getVertices(), 18 * sizeof(GLfloat));
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[k]), vertices[k], GL_STATIC_DRAW);
				shader->setUniform4f(COLOR_MATRIX, board->getBlockComponent(j, i)->getColor());
				++k;
				glDrawArrays(GL_TRIANGLES, 0, 6);
			}
		}
	}
	window->update();
}