#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "system.h"

#include "components/shadercomponent.h"
#include "components/component.h"
#include <vector>
#include <map>

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
  std::vector<std::string> Requires() {return {"GlfwSystem"};};

  void Enable(ShaderComponent& s);
  unsigned int GetUniformLocation(ShaderComponent& s, std::string name);
  void SetMartix4fUniform(unsigned int location, glm::mat4* data);
  void SetFloat4fUniform(unsigned int location, glm::vec4* data);
  void SetFloatUniform(unsigned int location, float data);
  void SetIntUniform(unsigned int location, int data);
private:
  void initialize(ShaderComponent& s);
  uint constructShader(std::string shaderFileName);
  void destruct(ShaderComponent& s);
  std::vector<ShaderComponent*> shaders;
  std::map<ComponentID, uint> program;
};

