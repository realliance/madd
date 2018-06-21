#ifndef MADD_H
#define MADD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "shaderprogram.h"
#include "gameobject.h"

class Madd {
public:
  Madd(int width, int height, const char *title);
  ~Madd();
  void Tick();
  void addObject(GameObject* obj);
  bool stayOpen(){return !close;}
private:
  GLFWwindow *window = nullptr;
  std::vector<GameObject*> objs;
  void ProcessInput();
  
  #pragma message "Delete these functions later " __FILE__
  bool ReloadShader();
  ShaderProgram* program;
  int shaderTimeLocation;
  bool close;
};

#endif // MADD_H