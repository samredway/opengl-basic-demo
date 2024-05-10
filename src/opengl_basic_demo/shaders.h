#ifndef OPENGL_BASIC_DEMO_BASIC_FRAGMENT_SHADER_H
#define OPENGL_BASIC_DEMO_BASIC_FRAGMENT_SHADER_H

#include <glad/glad.h>
#include <string>

#include "exceptions.h"

namespace opengl_basic_demo {

class Shader {
public:
    Shader() = default;
    ~Shader() { deleteGlObj(); }

    virtual void initialise() = 0;
    unsigned int getId() { return m_shaderId; }
    void deleteGlObj() { glDeleteShader(m_shaderId); }

private:
    unsigned int m_shaderId;
};


class BasicVertexShader : public Shader{
public:
    BasicVertexShader() = default;

    ~BasicVertexShader() { deleteShaderObj(); }

    // set up vertex buffer and compile the shader source code
    void initialise();

    unsigned int getId() { return m_vertexShaderId; }

    // delete the underlying gl shader c object - once it is passed into the gpu
    // we only need to keep the shader id
    void deleteShaderObj() { glDeleteShader(m_vertexShaderId); }

    // write data to buffer and specify draw type. GL_STATIC_DRAW is used to 
    // re-use the same vertex data many times without needing to resend or update
    void writeToBuffer(float vertices[]) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

private:
    // members
    unsigned int m_vertexBufferObjectId;
    unsigned int m_vertexShaderId;

    // define shaders in GLSL (graphics library shading language)
    // these get dynamically compiled at run time
    // vertex shader simpler declares location as 0 and defines
    // aPos as a 3d vector which its main function translating 
    // the input vector into a vec4 (the 4th is for perspective
    // division)
    const char* m_vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    // creates a vertex buffer object which can be used to pass in the vertices
    // that will get drawn. The buffer is bound to target GL_ARRAY_BUFFER which
    // is used for vertex attribute data
    void createArrayBuffer() {
        size_t numberOfBuffers {1};
        glGenBuffers(numberOfBuffers, &m_vertexBufferObjectId);  
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);
    }
};


class BasicFragmentShader {
public:
    BasicFragmentShader() = default;

    ~BasicFragmentShader() { deleteShaderObj(); }

    void initialise() {
        // compile shader from source
        m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(m_fragmentShaderId, 1, &m_fragmentShaderSource, NULL);
        glCompileShader(m_fragmentShaderId);
    }

    unsigned int getId() {
        return m_fragmentShaderId;
    }

    // delete the underlying gl shader c object - once it is passed into the gpu
    // we only need to keep the shader id
    void deleteShaderObj() { glDeleteShader(m_fragmentShaderId); }


private:
    unsigned int m_fragmentShaderId;

    // shader source gets compiled for use in GPU
    const char* m_fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
};

}  // opengl_basic_demo

#endif
