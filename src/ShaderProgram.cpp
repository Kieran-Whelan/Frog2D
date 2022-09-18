#include "ShaderProgram.h"

std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	try
	{
			std::string vertexCode = vertexFile;
			std::string fragmentCode = fragmentFile;

			//const char* vertexSource = vertexCode.c_str();
			//const char* fragmentSource = fragmentCode.c_str();

			const char* vertexSource = vertexFile;
			const char* fragmentSource = fragmentFile;

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexSource, NULL);
			glCompileShader(vertexShader);
			compileErrors(vertexShader, "VERTEX");

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
			glCompileShader(fragmentShader);
			compileErrors(fragmentShader, "FRAGMENT");

			ID = glCreateProgram();

			glAttachShader(ID, vertexShader);
			glAttachShader(ID, fragmentShader);
			glLinkProgram(ID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

void ShaderProgram::bind()
{
	glUseProgram(ID);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::remove()
{
	glDeleteProgram(ID);
}

void ShaderProgram::setUniform(const char* uniformName, glm::mat4 matrix4f)
{
	GLuint uniformLocation = glGetUniformLocation(ID, uniformName);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix4f));
}

void ShaderProgram::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR: " << type << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR: " << type << std::endl;
		}
	}
}

