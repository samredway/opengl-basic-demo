#include "shaders.hpp"


namespace opengl_basic_demo {


void Shader::checkCompileErrors() {
    int success;
    char infoLog[512];
    glGetShaderiv(m_glObjId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_glObjId, 512, NULL, infoLog);
        throw GlObjectException(infoLog);
    }
}


void VertexShader::initialise() {
    m_glObjId = glCreateShader(GL_VERTEX_SHADER);
    checkObjectCreateSuccess();

    // compile shader
    GLsizei numberOfShaders{1};
    glShaderSource(m_glObjId, numberOfShaders, &m_shaderSource, NULL);
    glCompileShader(m_glObjId);
    checkCompileErrors();
}


void FragmentShader::initialise() {
    // compile shader from source
    m_glObjId = glCreateShader(GL_FRAGMENT_SHADER);
    checkObjectCreateSuccess();

    // compile shader
    GLsizei numberOfShaders{1};
    glShaderSource(m_glObjId, numberOfShaders, &m_shaderSource, NULL);
    glCompileShader(m_glObjId);
    checkCompileErrors();
}


void ShaderProgram::initialise() {
    // create shader program 
    m_glObjId = glCreateProgram();
    checkObjectCreateSuccess();

    // attach shaders to underlying internal gl program
    for (Shader* shader : m_orderedShaders) {
        glAttachShader(m_glObjId, shader->getId());
    }
    // link internal shaders
    glLinkProgram(m_glObjId);

    // check for success and get relevant error log
    int success;
    char infoLog[512];
    glGetProgramiv(m_glObjId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_glObjId, 512, NULL, infoLog);
        throw GlObjectException(infoLog);
    }

    // Now they are linked internally we no longer need the local shader objs
    clearOrderedShaders();
}

}  // opengl_basic_demo
