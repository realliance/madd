#pragma once

#include <vector>
#include <chrono>
#include <map>
/** Type Definition for chrono clock shorthand */
using Clock = std::chrono::high_resolution_clock;
/** Type Definition for chrono time_point shorthand */
using Time = Clock::time_point;

#include "components/cameracomponent.h"
#include "components/keyboardeventcomponent.h"
#include "components/component.h"
#include "system.h"

struct GLFWwindow;
class Madd {
public:
  void Init(int width, int height, const char *title);
  static Madd& GetInstance();
  ~Madd();
  void Register(System* s);
  void Unregister(System* s);
  System* GetSystem(std::string s);
  ComponentID GetNewComponentID();

  void Tick();
  bool StayOpen(){return !close;}
  void Close(){close = true;}
  void SetMainCamera(CameraComponent* cameraObj);
  CameraComponent* GetMainCamera();
  double GetTime();
  float GetDeltaTime();
  int GetWidth();
  int GetHeight();
  GLFWwindow* GetWindow();
  static void ProcessInput(Component* c, int key, int action);
  Madd(const Madd&) = delete;
  Madd& operator=(const Madd&) = delete;
private:
  Madd() = default;
  std::map<std::string,System*> systems;
  ComponentID currID;

  CameraComponent* mainCamera;
  KeyboardEventComponent reloadShaderEvent;
  KeyboardEventComponent exitEvent;
  void ReloadShader();
  void UpdateDeltaTime();
  std::chrono::duration<float> dTime;
  bool close = false;
  int width;
  int height;
  float timeScale = 1.0f;
  Time lastFrame = Clock::now();
};

