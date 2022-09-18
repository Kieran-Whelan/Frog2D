#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <vector>
#include <glm/glm.hpp>

#include "VAO.hpp";
#include "VBO.hpp";

class Sprite
{
	public:
		std::vector<glm::vec3> vertices;
		VAO vao;
		Sprite(std::vector<glm::vec3> vec);

		void bind();
		void unbind();
};

#endif

