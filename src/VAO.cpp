#include "VAO.hpp";

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::link(VBO VBO)
{
    VBO.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::remove()
{
    glDeleteVertexArrays(1, &ID);
}
