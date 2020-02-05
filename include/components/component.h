#pragma once

#include <sys/types.h>
#include "componentdata.h"
typedef u_int64_t ComponentID;

struct Component{
  ComponentID cID;
  bool update;
  ComponentData* data;
  private:   virtual void _(){};
};

