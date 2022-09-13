#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class VBO
{
	public:
		GLuint ID;
        VBO(std::vector<glm::vec3> vertices);

		void bind();
		void unbind();
		void remove();

};

#endif

