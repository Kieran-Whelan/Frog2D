#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "ShaderProgram.hpp";
#include "Transformation.hpp";
#include "Sprite.hpp";

const unsigned int width = 1600;
const unsigned int height = 900;
const char* title = "Frog2D";

void getDesktopResolution(int& horizontal, int& vertical)
{
   RECT desktop;

   const HWND hDesktop = GetDesktopWindow();

   GetWindowRect(hDesktop, &desktop);

   horizontal = desktop.right;
   vertical = desktop.bottom;
}

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
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //borderless
    //glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); //fullscreen

    int horizontal = 0;
    int vertical = 0;
    getDesktopResolution(horizontal, vertical);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    //sets window to center of screen 
    glfwSetWindowPos(window, horizontal / 2 - width / 2, vertical / 2 - height / 2);
    //glfwSetWindowPos(window, 0, 0); //fullscreen
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    //glViewport(0, 0, 1920, 1080); //fullscreen
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

    Sprite sprite(quadVertices);

    ShaderProgram shaderProgram("vertex.glsl", "fragment.glsl");
    glm::vec2 position = glm::vec2(0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.17f, 0.13f, 0.17f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
        {
            position.y += 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        {
            position.y -= 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
        {
            position.x += 0.01f;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        {
            position.x -= 0.01f;
        }

        shaderProgram.bind();
        shaderProgram.setUniform("transformationMatrix", getTransformationMatrix(position));

        sprite.bind();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quadVertices.size());
        sprite.unbind();

        shaderProgram.unbind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}