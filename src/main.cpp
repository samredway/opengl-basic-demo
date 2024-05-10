#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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


    // create shader program to link the two shaders so output of vertex goes
    // to input of fragment and run the shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader.getId());
    glAttachShader(shaderProgram, fragmentShader.getId());
    glLinkProgram(shaderProgram);

    int success;
    const size_t logBufferSize{512};
    char infoLog[logBufferSize];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        // TODO handle error
    }
    glUseProgram(shaderProgram);



    // teardown underlying c object
    fragmentShader.deleteGlObj();
    vertexShader.deleteGlObj();
}
