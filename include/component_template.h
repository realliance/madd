#pragma once

#include "component.h"
#include <sys/types.h>

struct TemplateComponent : public Component{
  static ComponentType cType;
};

