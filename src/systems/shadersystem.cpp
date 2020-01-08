#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include "shadersystem.h"
#include "shadercomponent.h"
#include "glfwsystem.h"
#include "madd.h"

void ShaderSystem::Init(){
  activeProgram.ID = static_cast<uint>(-1);
}

ShaderSystem::~ShaderSystem(){
    for(ShaderComponent* s : shaders){
      destruct(*s);
    }
}

bool ShaderSystem::Register(Component* component){
  component->cID = Madd::GetInstance().GetNewComponentID();
  initialize(*dynamic_cast<ShaderComponent *>(component));
  shaders.push_back(dynamic_cast<ShaderComponent *>(component));
  return true;
}

bool ShaderSystem::Unregister(Component* component){
  for (auto i = begin(shaders); i != end(shaders); i++) {
    if ((*i)->cID == component->cID) {
      destruct(**i);
      shaders.erase(i);
      program.erase(component->cID);
      return true;
    }
  }
  return false;
}

void ShaderSystem::Update(){
}

void ShaderSystem::destruct(ShaderComponent& s){
  if(GlfwSystem::GetCurrentWindow() != NULL){
    glDeleteProgram(program[s.cID].ID);
  }
}

void ShaderSystem::initialize(ShaderComponent& s){
    uint vsID = constructShader(s.vertexShaderPath);
    uint fsID = constructShader(s.fragmentShaderPath);

    program[s.cID].ID = glCreateProgram();
    glAttachShader(program[s.cID].ID, vsID);
    glAttachShader(program[s.cID].ID, fsID);
    glLinkProgram(program[s.cID].ID);

    int success = 2;
    char infoLog[512];
    glGetProgramiv(program[s.cID].ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program[s.cID].ID, 512, NULL, infoLog);
        throw std::string("ERROR::SHADER::LINKING_FAILED\n") + infoLog;
    }
    if(success == 2){
        throw "UNKNOWN_OPENGL_ERROR";
    }

    glDetachShader(program[s.cID].ID, vsID);
    glDeleteShader(vsID);
    glDetachShader(program[s.cID].ID, fsID);
    glDeleteShader(fsID);

    program[s.cID].shade = GetUniformLocation(s, "shade");
    program[s.cID].model = GetUniformLocation(s, "model");
    program[s.cID].view = GetUniformLocation(s, "view");
    program[s.cID].projection = GetUniformLocation(s, "projection");
    program[s.cID].time = GetUniformLocation(s, "time");
    program[s.cID].textureEnabled = GetUniformLocation(s, "textureEnabled");
}

#define VERTEX_SHADER 'v'
#define FRAGMENT_SHADER 'f'

uint ShaderSystem::constructShader(std::string shaderFileName){
    char type = shaderFileName.at(shaderFileName.find(".") + 1);

    uint shaderType;
    if (type == VERTEX_SHADER)
        shaderType = GL_VERTEX_SHADER;
    else if (type == FRAGMENT_SHADER)
        shaderType = GL_FRAGMENT_SHADER;

    std::ifstream file;
    file.open("shaders/" + shaderFileName);
    if (file.peek() == std::ifstream::traits_type::eof())
        throw "SHADER_FILE_NOT_FOUND";
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
        throw "COMPILATION_FAILED";
    }
    return id;
}

#undef VERTEX_SHADER
#undef FRAGMENT_SHADER



void ShaderSystem::Enable(ShaderComponent& s){
  if(s.cID != activeProgram.ID){
    activeProgram = program[s.cID];
    glUseProgram(activeProgram.ID);
    if(s.enableCulling){
      glEnable(GL_CULL_FACE);
    }
  }
}


unsigned int ShaderSystem::GetUniformLocation(ShaderComponent& s, std::string name){
    return glGetUniformLocation(program[s.cID].ID, name.c_str());
}

void ShaderSystem::SetIntUniform(unsigned int location, int data){
    glUniform1i(location, data);
}

void ShaderSystem::SetMartix4fUniform(unsigned int location, glm::mat4* data){
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*data));
}

void ShaderSystem::SetFloat4fUniform(unsigned int location, glm::vec4* data){
    glUniform4fv(location, 1, glm::value_ptr(*data));
}

void ShaderSystem::SetFloatUniform(unsigned int location, float data){
    glUniform1f(location, data);
}

void ShaderSystem::SetShade(ShaderComponent& s, glm::vec4* shade){
  SetFloat4fUniform(activeProgram.shade, shade);
}

void ShaderSystem::SetModel(ShaderComponent& s, glm::mat4* model){
  SetMartix4fUniform(activeProgram.model, model);
}

void ShaderSystem::SetView(ShaderComponent& s, glm::mat4* view){
  SetMartix4fUniform(activeProgram.view, view);
}

void ShaderSystem::SetProjection(ShaderComponent& s, glm::mat4* projection){
  SetMartix4fUniform(activeProgram.projection, projection);
}

void ShaderSystem::SetTime(ShaderComponent& s, double time){
  SetFloatUniform(activeProgram.time, time);
}

void ShaderSystem::SetTextureEnabled(ShaderComponent& s, bool enabled){
  SetIntUniform(activeProgram.textureEnabled, enabled ? 1 : 0);
}
