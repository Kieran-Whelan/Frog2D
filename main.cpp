#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <vector>

#include "ShaderProgram.h";
#include "Transformation.h";
#include "VBO.h";
#include "VAO.h";

const unsigned int width = 1600;
const unsigned int height = 900;
const char* title = "Frog2D";

int main()
{
    glfwInit();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //borderless

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwSetWindowPos(window, 100, 100);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, width, height);

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

    VAO vao;
    vao.bind();

    VBO vbo(quadVertices);
    vao.link(vbo);
    vao.unbind();

    ShaderProgram shaderProgram("vertex.glsl", "fragment.glsl");
    glm::vec2 position = glm::vec2(0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.17f, 0.13f, 0.17f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.y += 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.y -= 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position.x += 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position.x -= 0.01f;
        }

        shaderProgram.bind();
        shaderProgram.setUniform("transformationMatrix", getTransformationMatrix(position));

        vao.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVertices.size());
        vao.unbind();

        shaderProgram.unbind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
