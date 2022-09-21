#include "Window.hpp"

Window::Window(char* title, unsigned int width, unsigned int height)
{
    this->title = title;
    this->width = width;
    this->height = height;

    glfwInit();

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE); //borderless
    //glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); //fullscreen
}

RECT Window::getDesktop()
{
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);
    return desktop;
}

float Window::getWindowX()
{
    return getDesktop().right;
}

float Window::getWindowY()
{
    return getDesktop().bottom;
}

int Window::createWindow()
{
    this->window = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);

    //sets window to center of screen 
    glfwSetWindowPos(window, getWindowX() / 2 - width / 2, getWindowY() / 2 - height / 2);
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
    glViewport(0, 0, this->width, this->height);
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(this->window);
}

void Window::quit()
{
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

bool Window::isQuit()
{
    return glfwWindowShouldClose(this->window);
}

GLFWwindow* Window::getWindow()
{
    return this->window;
}