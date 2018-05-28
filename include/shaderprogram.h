#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <iostream>

#include "shader.h"
#define LINKING_FAILED 20

class ShaderProgram {
public:
  ShaderProgram(std::string vsPath, std::string fsPath);
  ~ShaderProgram();
  unsigned int GetID() { return id; }

private:
  unsigned int id=0;
};

#endif // SHADERPROGRAM_H