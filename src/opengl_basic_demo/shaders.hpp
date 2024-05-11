#ifndef OPENGL_BASIC_DEMO_SHADER_H
#define OPENGL_BASIC_DEMO_SHADER_H

#include <glad/glad.h>
#include <string>
#include <vector>

#include "exceptions.hpp"

namespace opengl_basic_demo {


class Shader {
public:
    Shader() = default;
    virtual ~Shader() { deleteGlObj(); }

    // any initial setup and compile the shader source code
    virtual void initialise() = 0;
    virtual unsigned int getId() { return m_shaderId; }

    // delete the underlying gl shader c object - once it is passed into the gpu
    // we only need to keep the shader id
    virtual void deleteGlObj() { glDeleteShader(m_shaderId); }

private:
    unsigned int m_shaderId;
};


class VertexShader : public Shader{
public:
    VertexShader() = default;

    // set up vertex buffer and compile the shader source code
    virtual void initialise();

    // write data to buffer and specify draw type. GL_STATIC_DRAW is used to 
    // re-use the same vertex data many times without needing to resend or update
    void writeToBuffer(float vertices[]) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

private:
    unsigned int m_shaderId;
    unsigned int m_vertexBufferObjectId;

    // define shaders in GLSL (graphics library shading language)
    // these get dynamically compiled at run time
    // vertex shader simpler declares location as 0 and defines
    // aPos as a 3d vector which its main function translating 
    // the input vector into a vec4 (the 4th is for perspective
    // division)
    const char* m_shaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
};


class FragmentShader : public Shader {
public:
    FragmentShader() = default;

    virtual void initialise() {
        // compile shader from source
        m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);
        GLsizei numberOfShaders{1};
        glShaderSource(m_shaderId, numberOfShaders, &m_shaderSource, NULL);
        glCompileShader(m_shaderId);
    }

private:
    unsigned int m_shaderId;
    const char* m_shaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
};


// Takes a vector which contains an ordered collection of shaders to be run
// The output of the first being passed to the input of the next and so on.
class ShaderProgram {
public:
    ShaderProgram(std::vector<Shader*> orderedShaders)
        : m_orderedShaders(orderedShaders) {}

    ~ShaderProgram() {
        for (Shader* shader : m_orderedShaders) {
            delete(shader);
        }
    }

    void initialise();

    // Method to run program
    void run() { glUseProgram(m_shaderProgramId); }

private:
    unsigned int m_shaderProgramId;
    std::vector<Shader*> m_orderedShaders;
};

}  // opengl_basic_demo

#endif
