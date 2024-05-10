#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "opengl_basic_demo/application_window.h"
#include "opengl_basic_demo/basic_fragment_shader.h"
#include "opengl_basic_demo/basic_vertex_shader.h"
#include "opengl_basic_demo/exceptions.h"

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
    opengl_basic_demo::ApplicationWindow window{SCR_WIDTH , SCR_HEIGHT, WINDOW_TITLE};

    try {
        window.start();
    } catch (opengl_basic_demo::ApplicationWindowException ex) {
        std::cout << "Error opening window " << ex.what() << std::endl;
    }

    opengl_basic_demo::BasicVertexShader vertexShader{};

    try {
        vertexShader.initialise();
    } catch (opengl_basic_demo::VertexShaderException ex) {
        std::cout << "Error initialising vertex shader" << ex.what() << std::endl;
    }

    vertexShader.writeToBuffer(vertices);
}
