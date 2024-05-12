#ifndef OPENGL_BASIC_DEMO_SHADER_HPP
#define OPENGL_BASIC_DEMO_SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <vector>

#include "exceptions.hpp"


namespace opengl_basic_demo {


class GlObjectWrapper {
public:
    GlObjectWrapper() = default;
    ~GlObjectWrapper() {}

    virtual unsigned int getId() { return m_glObjId; }

    // any initial setup and compilation of shader source code 
    virtual void initialise() = 0;

protected:
    unsigned int m_glObjId;
    virtual void deleteGlObj() = 0;

    // calls to glCreate<Object> functions return an obj id or 0 in case
    // of failure
    void checkObjectCreateSuccess() {
        if (m_glObjId == 0) {
            throw GlObjectException("underlying gl object not created");
        }
    }
};


class Shader : public GlObjectWrapper {
public:
    Shader() = default;
    virtual ~Shader() { deleteGlObj(); }

protected:
    virtual void deleteGlObj() { 
        glDeleteShader(m_glObjId);
    }
    virtual void checkCompileErrors();
};


class VertexShader : public Shader{
public:
    VertexShader() = default;

    // set up vertex buffer and compile the shader source code
    virtual void initialise();

private:
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

    virtual void initialise();

private:
    const char* m_shaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";
};


// Takes a vector which contains an ordered collection of shaders to be run
// The output of the first being passed to the input of the next and so on.
class ShaderProgram : public GlObjectWrapper{
public:
    ShaderProgram(std::vector<Shader*> orderedShaders)
        : m_orderedShaders(orderedShaders) {}

    virtual void initialise();

    // Method to run program
    void run() { glUseProgram(m_glObjId); }

protected:
    virtual void deleteGlObject() {
        clearOrderedShaders();
        glDeleteProgram(m_glObjId);
    }

private:
    std::vector<Shader*> m_orderedShaders;

    void clearOrderedShaders() {
        for (Shader* shader : m_orderedShaders) {
            delete(shader);
        }
        m_orderedShaders.clear();
    }
};

}  // opengl_basic_demo

#endif
