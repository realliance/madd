#pragma once

#include <sys/types.h>
typedef size_t ComponentID;

struct Component{
  virtual ~Component() = default;
  ComponentID cID;
  bool update;
};

