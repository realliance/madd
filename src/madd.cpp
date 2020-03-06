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
  for(const ComponentType& cType: s->Types()){
    if(systemTypes.contains(cType)){
      throw "Type claimed by two systems.";
    }
    systemTypes[cType] = s;
  }
  if(systems.contains(s->Name())){
    throw "Two Systems share the same name.";
  }
  systems[s->Name()] = s;
}

bool Madd::RegisterComponent(Component* c){
  return systemTypes[c->Type()]->Register(c);
}

bool Madd::UnRegisterComponent(Component* c){
  return systemTypes[c->Type()]->Unregister(c);
}

System* Madd::GetSystem(std::string s){
  if(systems.contains(s)){
    return systems[s];
  }
  return nullptr;
}

ComponentID Madd::currID = 0;
ComponentID Madd::GetNewComponentID(){
  return ++currID;
}

ComponentType Madd::currType = 0;
ComponentType Madd::GetNewComponentType(){
  return ++currType;
}

bool Madd::InitSystems(){
  std::set<std::string> init;
  std::stack<std::pair<std::string,std::string>> requireStack;
  for(auto& [str, s] : systems){
    if(!init.contains(str)){
      requireStack.push({str,s->Name()});
      size_t stackSize = requireStack.size();
      do{
        if(!systems.contains(requireStack.top().first)){
          std::cout << requireStack.top().first << " is required by " << requireStack.top().second << " but not included." << std::endl;
          return false;
        }
        System* initsys = systems[requireStack.top().first];
        for(auto const& require: initsys->Requires()){
          if(!init.contains(require)){
            requireStack.push({require,initsys->Name()});
          }
        }
        if(stackSize == requireStack.size()){
          systems[requireStack.top().first]->Init();
          init.insert(requireStack.top().first);
          requireStack.pop();
        }
        stackSize = requireStack.size();
      }while(!requireStack.empty());
    }
  }
  return true;
}

void Madd::Run(){
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

void Madd::UpdateDeltaTime(){
  dTime = Clock::now() - lastFrame;
  lastFrame = Clock::now();
}


double Madd::GetTime(){return glfwGetTime();}
float Madd::GetDeltaTime(){return dTime.count() * timeScale;}
