#ifndef SHADERPROGRAM_CLASS_H
#define SHADERPROGRAM_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <cerrno>

std::string getFileContents(const char* filename);

class ShaderProgram
{
	public:
		GLuint ID;
		ShaderProgram(const char* vertexFile, const char* fragmentFile);

		void bind();
		void unbind();
		void remove();
		void setUniform(const char* uniformName, glm::mat4 matrix4f);
		void compileErrors(unsigned int shader, const char* type);
};

#endif