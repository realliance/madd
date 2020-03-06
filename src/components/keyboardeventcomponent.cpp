#include "keyboardeventcomponent.h"
#include "madd.h"

ComponentType KeyboardEventComponent::cType = Madd::GetNewComponentType();
ComponentType KeyboardEventComponent::Type(){ return cType; }
