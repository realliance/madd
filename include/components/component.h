#pragma once

#include <sys/types.h>
typedef u_int64_t ComponentID;
typedef u_int32_t ComponentType;

struct Component{
  ComponentID cID;
  bool update;
  virtual ComponentType Type() = 0;
};

