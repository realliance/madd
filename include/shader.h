#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

class Shader {
public:
  Shader(std::string shaderSourceCode, unsigned int shaderType);
  Shader(std::string shaderFileName);
  ~Shader();
  int GetID() { return id; }
  bool compiled() { return success; }

private:
  void Init();
  unsigned int id;
  unsigned int shaderType;
  const char *source;
  int success;
};

#endif // SHADER_H