#include "shaders.hpp"
#include <iostream>


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
    

    // // creates a vertex buffer object which can be used to pass in the vertices
    // // that will get drawn. The buffer is bound to target GL_ARRAY_BUFFER which
    // // is used for vertex attribute data
    // GLsizei numberOfBuffers {1};
    // glGenBuffers(numberOfBuffers, &m_vertexBufferObjectId);  
    // glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);
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
    unsigned int m_shaderProgramId;
    m_shaderProgramId = glCreateProgram();

    // 0 output indicates error
    if (m_shaderProgramId == 0) {
        throw GlObjectException("underlying gl object not created");
    }
    
    // attach shaders to underlying internal gl program
    for (Shader* shader : m_orderedShaders) {
        glAttachShader(m_shaderProgramId, shader->getId());
    }
    // link internal shaders
    glLinkProgram(m_shaderProgramId);

    // check for success and get relevant error log
    int success;
    char infoLog[512];
    glGetProgramiv(m_shaderProgramId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_shaderProgramId, 512, NULL, infoLog);
        throw GlObjectException(infoLog);
    }

    // Now they are linked internally we no longer need the local shader objs
    clearOrderedShaders();
}

}  // opengl_basic_demo
