#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include "shader.h"
#define LINKING_FAILED 20

class ShaderProgram {
public:
  ShaderProgram(Shader *vs, Shader *fs);
  ~ShaderProgram();
  unsigned int GetID() { return id; }

private:
  unsigned int id;
};

#endif // SHADERPROGRAM_H