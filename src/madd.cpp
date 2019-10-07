#include "madd.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "rendersystem.h"
#include "camerasystem.h"
#include "keyboardeventsystem.h"
#include "mouseeventsystem.h"
#include "keycodes.h"

void Madd::Init() {
  this->currID = 0;
  reloadShaderEvent = KeyboardEventComponent{};
  reloadShaderEvent.callback = Madd::ProcessInput;
  exitEvent = reloadShaderEvent;
  exitEvent.code = KEY_ESCAPE;
  reloadShaderEvent.code = KEY_SPACE;
}

void Madd::Deinit() {
  for(auto const& [name, sys] : systems){
    sys->Deinit();
  }
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
  for(auto& [str, s] : systems){
    s->Init();
  }
}

void Madd::Run(){
  KeyboardEventSystem::GetInstance().Register(&reloadShaderEvent);
  KeyboardEventSystem::GetInstance().Register(&exitEvent);
  while(StayOpen()){
    Tick();
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

