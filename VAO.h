#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h";

class VAO
{
	public:
		GLuint ID;
		VAO();

		void link(VBO VBO);
		void bind();
		void unbind();
		void remove();
};

#endif

