#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "system.h"

#include "components/shadercomponent.h"
#include <vector>

struct Shader{
  unsigned int id;
  unsigned int shaderType;
  unsigned int program;
};
class ShaderSystem : public System{
public:

  void Init();
  void Deinit();
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();

  std::string Name() { return "ShaderSystem"; }

  static void Enable(ShaderComponent& s);
  static unsigned int GetUniformLocation(ShaderComponent& s, std::string name);
  static void SetMartix4fUniform(unsigned int location, glm::mat4* data);
  static void SetFloat4fUniform(unsigned int location, glm::vec4* data);
  static void SetFloatUniform(unsigned int location, float data);
  static void SetIntUniform(unsigned int location, int data);
private:
  void initialize(ShaderComponent& s);
  uint constructShader(std::string shaderFileName);
  void destruct(ShaderComponent& s);
  std::vector<ShaderComponent*> shaders;

};

