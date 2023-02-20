#include <glad/glad.h> //glad always needs to go above glfw
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "core/ShaderProgram.hpp";
#include "core/Sprite.hpp";
#include "core/math/Transformation.hpp"
#include "core/Window.hpp"

const unsigned int width = 1600;
const unsigned int height = 900;
char* title = "Frog2D";

/*
    Note to self: build using vscode cmake: build command
*/
int main()
{
    Window window(title, width, height);
    window.createWindow();

    float triangle_vertices[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    std::vector<glm::vec3> quadVertices;

    quadVertices.resize(6);

    quadVertices[0] = glm::vec3(0.5f, 0.5f, 0.0f);
    quadVertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
    quadVertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);
    quadVertices[3] = glm::vec3(-0.5f, -0.5f, 0.0f);
    quadVertices[4] = glm::vec3(0.5f, 0.5f, 0.0f);
    quadVertices[5] = glm::vec3(-0.5f, 0.5f, 0.0f);

    Sprite sprite(quadVertices);

    ShaderProgram shaderProgram("vertex.glsl", "fragment.glsl");
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    //2.0f scale fills full screen
    glm::vec2 scale = glm::vec2(2.0f, 2.0f);

    while (!window.isQuit()) {
        glClearColor(0.17f, 0.13f, 0.17f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }

        if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) 
        {
            position.y += 0.01f;
        }

        if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) 
        {
            position.y -= 0.01f;
        }

        if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) 
        {
            position.x += 0.01f;
        }

        if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) 
        {
            position.x -= 0.01f;
        }

        shaderProgram.bind();
        shaderProgram.setUniform("transformationMatrix", getTransformationMatrix(position, scale));

        sprite.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVertices.size());
        sprite.unbind();

        shaderProgram.unbind();

        window.update();
    }

    window.quit();
    return 0;
}