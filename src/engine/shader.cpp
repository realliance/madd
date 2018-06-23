#include "shader.h"
#include <iostream>
#include <fstream>

#define VERTEX_SHADER 'v'
#define FRAGMENT_SHADER 'f'

Shader::Shader(std::string shaderSourceCode, unsigned int shaderType):
        source(shaderSourceCode.c_str()),
        shaderType(shaderType),
        program(0) {
    Init();
}

Shader::Shader(std::string shaderFileName) {
    char type = shaderFileName.at(shaderFileName.find(".") + 1);

    if (type == VERTEX_SHADER)
        shaderType = GL_VERTEX_SHADER;
    else if (type == FRAGMENT_SHADER)
        shaderType = GL_FRAGMENT_SHADER;

    std::ifstream file;
    file.open("shaders/" + shaderFileName);
    std::string shaderSourceCode((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
    source = shaderSourceCode.c_str();
    Init();
}

void Shader::Init() {
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::" << (char)(VERTEX_SHADER-32) << "SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        throw COMPILATION_FAILED;
    }
}

Shader::~Shader() {
    if (program)
        glDetachShader(program, id);
    glDeleteShader(id);
}

int Shader::Link(unsigned int _program) {
    program = _program;
    return id;
}