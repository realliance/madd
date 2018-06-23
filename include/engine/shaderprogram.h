#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <iostream>
#include <glm/glm.hpp>
#include "shader.h"
#define LINKING_FAILED 20

class ShaderProgram {
public:
  ShaderProgram(std::string vsPath, std::string fsPath);
  ~ShaderProgram();
  unsigned int GetID() { return id; }
  void Enable();
  void AddInt(std::string name, int value);
  unsigned int GetUniformLocation(std::string name);
  static void SetMartix4fUniform(unsigned int location, glm::mat4* data);
  static void SetFloatUniform(unsigned int location, float data);
private:
  unsigned int id=0;
};

#endif // SHADERPROGRAM_H