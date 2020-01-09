#include "madd.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendersystem.h"
#include "camerasystem.h"
#include "keyboardeventsystem.h"
#include "mouseeventsystem.h"
#include "keycodes.h"
#include <stack>
#include <set>

void Madd::Init() {
  this->currID = 0;
  reloadShaderEvent = KeyboardEventComponent{};
  reloadShaderEvent.callback = Madd::ProcessInput;
  exitEvent = reloadShaderEvent;
  exitEvent.code = KEY_ESCAPE;
  reloadShaderEvent.code = KEY_SPACE;
  framecounter = 0;
  lastframecount = 0;
  close = false;
  timeScale = 1.0f;
  lastFPS = glfwGetTime();
  lastFrame = Clock::now();
}

void Madd::Deinit() {
  for(auto const& [name, sys] : systems){
    delete sys;
  }
  systems.clear();
}

Madd& Madd::GetInstance() {
  static Madd instance;
  return instance;
}

void Madd::Register(std::vector<System*> sys){
  for(System* s : sys){
    Register(s);
  }
}

void Madd::Register(System* s){
  if(systems.contains(s->Name())){
    return;
  }
  systems[s->Name()] = s;
}

System* Madd::GetSystem(std::string s){
  if(systems.contains(s)){
    return systems[s];
  }
  return nullptr;
}

size_t Madd::GetNewComponentID(){
  return ++currID;
}

void Madd::InitSystems(){
  std::set<std::string> init;
  std::stack<std::string> requireStack;
  for(auto& [str, s] : systems){
    if(!init.contains(str)){
      requireStack.push(str);
      size_t stackSize = requireStack.size();
      do{
        for(auto const& require: systems[requireStack.top()]->Requires()){
          if(!init.contains(require)){
            requireStack.push(require);
          }
        }
        if(stackSize == requireStack.size()){
          systems[requireStack.top()]->Init();
          init.insert(requireStack.top());
          requireStack.pop();
        }
        stackSize = requireStack.size();
      }while(!requireStack.empty());
    }
  }
}

void Madd::Run(){
  if(systems.contains("KeyboardEventSystem")){
    systems["KeyboardEventSystem"]->Register(&exitEvent);
  }
  while(StayOpen()){
    Tick();
    if(framecounter % 60 == 0){
      std::cout << (framecounter-lastframecount)/(GetTime()-lastFPS) << '\r' << std::flush;
      lastframecount = framecounter;
      lastFPS = GetTime();
    }
    framecounter++;
  }
}

void Madd::Tick(){
  for(auto const& [name, sys] : systems){
      sys->Update();
  }
  UpdateDeltaTime();
}

void Madd::ReloadShader() {
  // for(GameObject* obj : objs)
  //     if(!obj->ReloadShaders())
  //         return;
}

void Madd::ProcessInput(Component* c, WindowComponent* window, int key, int action){
  if (key == KEY_ESCAPE)
    GetInstance().Close();
  if (key == KEY_SPACE && action == KEY_PRESS)
    GetInstance().ReloadShader();
}

void Madd::UpdateDeltaTime(){
  dTime = Clock::now() - lastFrame;
  lastFrame = Clock::now();
}


double Madd::GetTime(){return glfwGetTime();}
float Madd::GetDeltaTime(){return dTime.count() * timeScale;}

