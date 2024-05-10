#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "opengl_basic_demo/application_window.h"
#include "opengl_basic_demo/exceptions.h"
#include "opengl_basic_demo/shaders.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* WINDOW_TITLE{"OpenGl Basic Demo"};

float vertices[] {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};


int main() {
    // open window
    opengl_basic_demo::ApplicationWindow window{SCR_WIDTH , SCR_HEIGHT, WINDOW_TITLE};
    try {
        window.start();
    } catch (opengl_basic_demo::ApplicationWindowException ex) {
        std::cout << "Error opening window " << ex.what() << std::endl;
    }

    // initialise vertex shader and write points
    opengl_basic_demo::VertexShader vertexShader{};
    try {
        vertexShader.initialise();
    } catch (opengl_basic_demo::VertexShaderException ex) {
        std::cout << "Error initialising vertex shader " << ex.what() << std::endl;
    }
    vertexShader.writeToBuffer(vertices);

    // initialise fragment shader
    opengl_basic_demo::FragmentShader fragmentShader{};
    fragmentShader.initialise();

    // teardown underlying c object
    fragmentShader.deleteGlObj();
    vertexShader.deleteGlObj();
}
