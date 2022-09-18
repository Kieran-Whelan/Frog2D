#include "Sprite.hpp";

Sprite::Sprite(std::vector<glm::vec3> vec)
{
	this->vertices = vec;
    VAO vao;
    this->vao = vao;
    vao.bind();

    VBO vbo(vec);
    vao.link(vbo);
    vao.unbind();
}

void Sprite::bind()
{
    this->vao.bind();
}

void Sprite::unbind()
{
    this->vao.unbind();
}
