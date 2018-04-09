#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <iostream>

class Shader {
public:
  Shader(std::string shaderSourceCode, unsigned int shaderType);
  ~Shader();
  int GetID() { return id; }
  bool compiled() { return success; }

private:
  unsigned int id;
  const char *source;
  int success;
};

#endif // SHADER_H