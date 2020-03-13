#pragma once

#include <sys/types.h>
typedef u_int64_t ComponentID;
typedef u_int32_t ComponentType;

struct Component{
  ComponentID cID;
  bool update;
  virtual ComponentType Type() = 0;
  Component(){
    cID = 0;
  };
  Component(const Component& c) {
    if(this != &c){
      cID = 0;
    }
  }
  Component& operator=(const Component& c){
    return *this;
  }
};

