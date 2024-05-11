#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "opengl_basic_demo/application_window.hpp"
#include "opengl_basic_demo/exceptions.hpp"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE{"OpenGl Basic Demo"};


int main() {

    // open window
    opengl_basic_demo::ApplicationWindow window{SCR_WIDTH , SCR_HEIGHT, WINDOW_TITLE};
    try {
        window.initialise();
        window.start();
    } catch (opengl_basic_demo::ApplicationWindowException ex) {
        std::cerr << "Error opening window: " << ex.what() << std::endl;
    }

    return 0;
}
