#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <vector>

#include "ShaderProgram.h";

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

    GLuint vertex_buffer_object = 0;
    glGenBuffers(1, &vertex_buffer_object);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, quad_vertices, GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(glm::vec3), quadVertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint vertex_array_object = 0;
    glGenVertexArrays(1, &vertex_array_object);
    {
        glBindVertexArray(vertex_array_object);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ShaderProgram shaderProgram("vertex.glsl", "fragment.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.17f, 0.13f, 0.17f, 1.0f);

        double current_seconds = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        shaderProgram.Bind();

        glBindVertexArray(vertex_array_object);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVertices.size());
        glBindVertexArray(0);

        shaderProgram.Unbind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
