#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "opengl_basic_demo/application_window.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE{"OpenGl Basic Demo"};

int main()
{
    opengl_basic_demo::ApplicationWindow window{SCR_WIDTH , SCR_HEIGHT, WINDOW_TITLE};
    window.start();
}
