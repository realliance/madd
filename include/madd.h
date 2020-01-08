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

struct WindowComponent;
class Madd {
public:
  void Init();
  static Madd& GetInstance();
  void Deinit();
  void Register(System* s);
  void Register(std::vector<System*> sys);
  void Unregister(System* s);
  void InitSystems();
  System* GetSystem(std::string s);
  ComponentID GetNewComponentID();

  void Run();
  void Tick();
  bool StayOpen(){return !close;}
  void Close(){close = true;}
  double GetTime();
  float GetDeltaTime();
  static void ProcessInput(Component* c, WindowComponent* window, int key, int action);
  Madd(const Madd&) = delete;
  Madd& operator=(const Madd&) = delete;
private:
  Madd() = default;
  std::map<std::string,System*> systems;
  ComponentID currID;
  
  KeyboardEventComponent reloadShaderEvent;
  KeyboardEventComponent exitEvent;
  void ReloadShader();
  void UpdateDeltaTime();
  std::chrono::duration<float> dTime;
  bool close;
  float timeScale;
  Time lastFrame;
  size_t framecounter;
  size_t lastframecount;
  double lastFPS;
};

