#include "shader.h"

Shader::Shader(std::string shaderSourceCode, unsigned int shaderType):source(shaderSourceCode.c_str()){
    id=glCreateShader(shaderType);

    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}