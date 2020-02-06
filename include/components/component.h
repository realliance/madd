#pragma once

#include <sys/types.h>
typedef u_int64_t ComponentID;

struct Component{
  ComponentID cID;
  bool update;
  private:   virtual void _(){};
};

