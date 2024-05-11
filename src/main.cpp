#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "opengl_basic_demo/application_window.hpp"
#include "opengl_basic_demo/exceptions.hpp"
#include "opengl_basic_demo/shaders.hpp"

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
    opengl_basic_demo::VertexShader* vertexShader = new opengl_basic_demo::VertexShader();
    try {
        vertexShader->initialise();
    } catch (opengl_basic_demo::VertexShaderException ex) {
        std::cout << "Error initialising vertex shader " << ex.what() << std::endl;
    }
    vertexShader->writeToBuffer(vertices);

    // initialise fragment shader
    opengl_basic_demo::FragmentShader* fragmentShader = new opengl_basic_demo::FragmentShader();
    fragmentShader->initialise();

    // Link shaders in a shader program and run
    std::vector<opengl_basic_demo::Shader*> shaders{vertexShader, fragmentShader};
    opengl_basic_demo::ShaderProgram shaderProgram{shaders};
    shaderProgram.initialise();
    shaderProgram.run();
}
