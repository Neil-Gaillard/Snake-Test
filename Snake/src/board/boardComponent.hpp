#pragma once

#include "GLFW/glfw3.h"

#include "../maths/vec2.hpp"
#include "../maths/vec4.hpp"

namespace board
{
	class BoardComponent
	{
	public:
		constexpr static int NUMBER_VERTICES = 18;

	private:
		const maths::vec2 m_position;

		GLfloat* m_vertices;

		bool m_active;
		maths::vec4 m_color;

	public:
		BoardComponent(const maths::vec2 position, const maths::vec4 color);
		BoardComponent(const maths::vec2 position, const maths::vec4 color, const bool active);

		inline bool isActive() const { return this->m_active; }
		inline maths::vec2 getPosition() const { return this->m_position; }
		inline maths::vec4 getColor() const { return this->m_color; }
		inline GLfloat* getVertices() const { return this->m_vertices; }

		inline void setActive(const bool active) { this->m_active = active; }
		inline void setColor(const maths::vec4 color) { this->m_color = color; }
	};
}