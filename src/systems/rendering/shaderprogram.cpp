#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include "shaderprogram.h"
#include "shadercomponent.h"

const char* GLErrorToString(GLenum err)
{
    switch (err)
    {
    case GL_NO_ERROR:                      return "GL_NO_ERROR";
    case GL_INVALID_ENUM:                  return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:                 return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:             return "GL_INVALID_OPERATION";
    // case GL_STACK_OVERFLOW:                return "GL_STACK_OVERFLOW";
    // case GL_STACK_UNDERFLOW:               return "GL_STACK_UNDERFLOW";
    case GL_OUT_OF_MEMORY:                 return "GL_OUT_OF_MEMORY";
    case 0x8031: /* not core */            return "GL_TABLE_TOO_LARGE_EXT";
    case 0x8065: /* not core */            return "GL_TEXTURE_TOO_LARGE_EXT";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
    default:
        assert(!"Unhandled GL error code");
        return NULL;
    }
}

ShaderComponent ShaderProgram::Construct(std::string vsPath, std::string fsPath){
    uint vsID = constructShader(vsPath);
    uint fsID = constructShader(fsPath);

    ShaderComponent s;
    s.id = glCreateProgram();
    glAttachShader(s.id, vsID);
    glAttachShader(s.id, fsID);
    glLinkProgram(s.id);

    int success = 2;
    char infoLog[512];
    glGetProgramiv(s.id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(s.id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
        throw LINKING_FAILED; 
    }
    if(success == 2){
        std::cout << "ERROR::UNKNOWN\n" << GLErrorToString(glGetError()) << std::endl;
        throw UNKNOWN_OPENGL_ERROR;
    }

    glDetachShader(s.id, vsID);
    glDeleteShader(vsID);
    glDetachShader(s.id, fsID);
    glDeleteShader(fsID);
    return s;
}

#define VERTEX_SHADER 'v'
#define FRAGMENT_SHADER 'f'

uint ShaderProgram::constructShader(std::string shaderFileName){
    char type = shaderFileName.at(shaderFileName.find(".") + 1);

    uint shaderType;
    if (type == VERTEX_SHADER)
        shaderType = GL_VERTEX_SHADER;
    else if (type == FRAGMENT_SHADER)
        shaderType = GL_FRAGMENT_SHADER;

    std::ifstream file;
    file.open("shaders/" + shaderFileName);
    if (file.peek() == std::ifstream::traits_type::eof())
        throw SHADER_FILE_NOT_FOUND;
    std::string shaderSourceCode((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
    uint id = glCreateShader(shaderType);
    const char* source = shaderSourceCode.c_str();
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
    return id;
}

#undef VERTEX_SHADER
#undef FRAGMENT_SHADER

void ShaderProgram::Destruct(ShaderComponent s){
    glDeleteProgram(s.id);
}

void ShaderProgram::Enable(ShaderComponent s){
    glUseProgram(s.id);
}


unsigned int ShaderProgram::GetUniformLocation(ShaderComponent s, std::string name){
    return glGetUniformLocation(s.id, name.c_str());
}

void ShaderProgram::SetIntUniform(unsigned int location, int data){
    glUniform1i(location, data);
}

void ShaderProgram::SetMartix4fUniform(unsigned int location, glm::mat4* data){
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*data));
}

void ShaderProgram::SetFloat4fUniform(unsigned int location, glm::vec4* data){
    glUniform4fv(location, 1, glm::value_ptr(*data));
}

void ShaderProgram::SetFloatUniform(unsigned int location, float data){
    glUniform1f(location, data);
}
