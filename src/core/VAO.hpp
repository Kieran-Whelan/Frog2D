#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.hpp";

class VAO
{
	private:
		GLuint id;

	public:
		VAO();

		void link(VBO VBO);
		void bind();
		void unbind();
		void remove();
};

#endif

