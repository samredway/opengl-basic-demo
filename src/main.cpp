#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "opengl_basic_demo/application_window.h"
#include "opengl_basic_demo/exceptions.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE{"OpenGl Basic Demo"};

int main() {
    opengl_basic_demo::ApplicationWindow window{SCR_WIDTH , SCR_HEIGHT, WINDOW_TITLE};

    try {
        window.start();
    }
    catch (opengl_basic_demo::ApplicationWindowException ex) {
        std::cout << "Error opening window " << ex.what() << std::endl;
    }
    
}
