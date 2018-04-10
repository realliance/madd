#ifndef MADD_H
#define MADD_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "shader.h"
#include "shaderprogram.h"
#include "shader_sources.h"
#include "vertexarray.h"

class Madd {
public:
  Madd(int width, int height, const char *title);
  ~Madd();
  void Start();

private:
  GLFWwindow *window = nullptr;

  void ProcessInput();
  
  #pragma message "Delete these functions later " __FILE__
  void ReloadShader();
  ShaderProgram* program;
};

#endif // MADD_H