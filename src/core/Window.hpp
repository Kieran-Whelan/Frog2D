#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

class Window
{
    private:
        char* title;
        unsigned int width;
        unsigned int height;
        GLFWwindow* window;

        float getWindowX();
        float getWindowY();
    public:
        Window(char* title, unsigned int width, unsigned int height);

        int createWindow();
        GLFWwindow* getWindow();
};

#endif