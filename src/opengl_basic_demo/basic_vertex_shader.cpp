#include "basic_vertex_shader.h"


namespace opengl_basic_demo {

void BasicVertexShader::createVertexShader() {
    m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    // compile shader source code
    size_t numberOfShaders {1};
    glShaderSource(m_vertexShaderId, numberOfShaders, &m_vertexShaderSource, nullptr);

    // check for success of compilation
    int success;
    glGetShaderiv(m_vertexShaderId, GL_COMPILE_STATUS, &success);

    if (!success) {   
        // retrieve log
        size_t logBufferSize {512};
        char infoLog[logBufferSize];
        glGetShaderInfoLog(m_vertexShaderId, logBufferSize, NULL, infoLog);
        std::string errMsg = std::string(infoLog);
        throw VertexShaderException(errMsg);
    }
}

}  // opengl_basic_demo
