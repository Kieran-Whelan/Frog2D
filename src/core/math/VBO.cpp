#include "VBO.hpp";

VBO::VBO(std::vector<glm::vec3> vertices)
{
    glGenBuffers(1, &this->id);
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove()
{
    glDeleteBuffers(1, &this->id);
}