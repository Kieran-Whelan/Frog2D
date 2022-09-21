#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
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
        RECT getDesktop();
    public:
        Window(char* title, unsigned int width, unsigned int height);

        int createWindow();
        void update();
        void quit();
        bool isQuit();
        GLFWwindow* getWindow();
};

#endif