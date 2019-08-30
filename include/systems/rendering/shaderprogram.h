#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "errors.h"

#include "components/shadercomponent.h"

struct Shader{
  unsigned int id;
  unsigned int shaderType;
  unsigned int program;
};
class ShaderProgram {
  public:
    ShaderProgram() = delete;
    static ShaderComponent Construct(std::string vsPath, std::string fsPath);
    static void Destruct(ShaderComponent s);
    static void Enable(ShaderComponent s);
    static unsigned int GetUniformLocation(ShaderComponent s, std::string name);
    static void SetMartix4fUniform(unsigned int location, glm::mat4* data);
    static void SetFloat4fUniform(unsigned int location, glm::vec4* data);
    static void SetFloatUniform(unsigned int location, float data);
    static void SetIntUniform(unsigned int location, int data);
  private:
    static uint constructShader(std::string shaderFileName);
};

