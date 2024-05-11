#include "shaders.hpp"


namespace opengl_basic_demo {


void VertexShader::initialise() {
    // creates a vertex buffer object which can be used to pass in the vertices
    // that will get drawn. The buffer is bound to target GL_ARRAY_BUFFER which
    // is used for vertex attribute data
    size_t numberOfBuffers {1};
    glGenBuffers(numberOfBuffers, &m_vertexBufferObjectId);  
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);

    m_shaderId = glCreateShader(GL_VERTEX_SHADER);

    // compile shader source code
    const size_t numberOfShaders{1};
    glShaderSource(m_shaderId, numberOfShaders, &m_shaderSource, nullptr);

    // check for success of compilation
    int success;
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &success);

    if (!success) {   
        // retrieve log
        const size_t logBufferSize{512};
        char infoLog[logBufferSize];
        glGetShaderInfoLog(m_shaderId, logBufferSize, NULL, infoLog);
        std::string errMsg = std::string(infoLog);
        throw VertexShaderException(errMsg);
    }
}


void ShaderProgram::initialise() {
    // create shader program 
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    // attach shaders to underlying internal gl program
    for (Shader* shader : m_orderedShaders) {
        glAttachShader(m_shaderProgramId, shader->getId());
    }
    // link internal shaders
    glLinkProgram(m_shaderProgramId);

    // Now they are linked internally we no longer need the local shader objs
    for (Shader* shader : m_orderedShaders) {
        shader->deleteGlObj();
    }

    // check for success and get relevant error log
    int success;
    const size_t logBufferSize{512};
    char infoLog[logBufferSize];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::string errMsg = std::string(infoLog);
        throw ShaderProgramException(errMsg);
    }
}

}  // opengl_basic_demo
