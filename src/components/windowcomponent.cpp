#include "windowcomponent.h"
#include "madd.h"

ComponentType WindowComponent::cType = Madd::GetNewComponentType();
ComponentType WindowComponent::Type(){ return cType; }
