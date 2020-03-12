#include "madd.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <stack>
#include <set>

void Madd::Init() {
  framecounter = 0;
  lastframecount = 0;
  close = false;
  timeScale = 1.0f;
  lastFPS = glfwGetTime();
  lastFrame = Clock::now();
}

void Madd::Deinit() {
  for(auto const& [name, sys] : systems){
    destruct(sys);
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
    systemStates[s->Type()] = SystemState::UNINITIALIZED;
  }
}

void Madd::Unregister(System* s){
  systems.erase(s->Name());
  for(const ComponentType& cType: s->ComponentTypes()){
    systemCTypes.erase(cType);
  }
  destruct(s);
}

void Madd::destruct(System* s){
  s->Deinit();
  systemSTypes.erase(s->Type());
  systemStates.erase(s->Type());
  delete s;
}

void Madd::Register(System* s){
  for(const ComponentType& cType: s->ComponentTypes()){
    if(systemCTypes.contains(cType)){
      throw "Type claimed by two systems.";
    }
    systemCTypes[cType] = s;
  }
  if(systems.contains(s->Name())){
    throw "Two Systems share the same name.";
  }
  systems[s->Name()] = s;
  systemSTypes[s->Type()] = s;
}

bool Madd::RegisterComponent(Component* c){
  return systemCTypes[c->Type()]->Register(c);
}

bool Madd::UnregisterComponent(Component* c){
  return systemCTypes[c->Type()]->Unregister(c);
}

System* Madd::GetSystem(std::string s){
  if(systems.contains(s)){
    return systems[s];
  }
  return nullptr;
}

ComponentID Madd::currentCID = 0;
ComponentType Madd::currentCType = 0;
SystemType Madd::currentSType = 0;

ComponentID Madd::GetNewComponentID(){
  return ++currentCID;
}
ComponentType Madd::GetNewComponentType(){
  return ++currentCType;
}
SystemType Madd::GetNewSystemType(){
  return ++currentSType;
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
          systemStates[systems[requireStack.top().first]->Type()] = SystemState::INITIALIZED;
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
