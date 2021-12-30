#include "boardComponent.hpp"

#include <cstring>

#include "board.hpp"

namespace board
{
	BoardComponent::BoardComponent(const maths::vec2 position, const maths::vec4 color) : BoardComponent(position, color, false)
	{
		
	}

	BoardComponent::BoardComponent(const maths::vec2 position, const maths::vec4 color, const bool active) :
		m_position(position), m_vertices(new GLfloat[NUMBER_VERTICES]), m_active(active), m_is_apple(false), m_color(color)
	{
		const GLfloat vertices[NUMBER_VERTICES] = 
		{
			static_cast<GLfloat>(this->m_position.get_y_pos()),
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()) - 1.0f, 0.0f,
			static_cast<GLfloat>(this->m_position.get_y_pos()),
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()), 0.0f,
			static_cast<GLfloat>(this->m_position.get_y_pos()) + 1.0f,
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()), 0.0f,
			static_cast<GLfloat>(this->m_position.get_y_pos()) + 1.0f,
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()), 0.0f,
			static_cast<GLfloat>(this->m_position.get_y_pos()) + 1.0f,
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()) - 1.0f, 0.0f,
			static_cast<GLfloat>(this->m_position.get_y_pos()),
			static_cast<GLfloat>(Board::SIZE) - static_cast<GLfloat>(this->m_position.get_x_pos()) - 1.0f, 0.0f
		};
		memcpy(this->m_vertices, vertices, sizeof(GLfloat) * NUMBER_VERTICES);
	}
}