#pragma once

#include <sys/types.h>
typedef u_int64_t ComponentID;

struct Component{
  // virtual ~Component() = default;
  virtual void _(){};
  ComponentID cID;
  bool update;
};

