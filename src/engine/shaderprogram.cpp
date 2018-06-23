#include <glm/gtc/type_ptr.hpp>

#include "shaderprogram.h"

ShaderProgram::ShaderProgram(std::string vsPath, std::string fsPath){
    Shader *vs;
    Shader *fs;
    try {
        vs = new Shader(vsPath);
        fs = new Shader(fsPath);
    } catch (int e){
        throw COMPILATION_FAILED;
    }

    id = glCreateProgram();
    glAttachShader(id, vs->Link(id));
    glAttachShader(id, fs->Link(id));
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
        throw LINKING_FAILED; 
    }

    delete vs;
    delete fs;
}

ShaderProgram::~ShaderProgram(){
    glDeleteProgram(id);
}

void ShaderProgram::Enable(){
    glUseProgram(id);
}

void ShaderProgram::AddInt(std::string name, int value){
    glUniform1i(glGetUniformLocation(id, name.c_str()), 1);
}

unsigned int ShaderProgram::GetUniformLocation(std::string name){
    return glGetUniformLocation(id, name.c_str());
}

void ShaderProgram::SetMartix4fUniform(unsigned int location, glm::mat4* data){
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*data));
}

void ShaderProgram::SetFloatUniform(unsigned int location, float data){
    glUniform1f(location, data);
}