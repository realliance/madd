#pragma once

#include "system.h"
#include "components/windowcomponent.h"
#include <string>
#include <vector>

class GLFWwindow;
class WindowSystem : public System{
public:
  void Init();
  void Deinit();;
  bool Register(Component* component);
  bool Unregister(Component* component);
  void Update();
  std::string Name() { return "WindowSystem"; }
  std::vector<WindowComponent*>& GetWindows();

  static void Enable(WindowComponent& w);
  static void Finish(WindowComponent& w);
  float GetAspectRatio(WindowComponent& w);
  static void LockCursor(WindowComponent& w);
  static void UnlockCursor(WindowComponent& w);
private:
  static void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void cursorCallBack(GLFWwindow *window, double xpos, double ypos);
  static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  static void errorCallback(int, const char* err_str);
  static void windowFocusCallback(GLFWwindow* window, int focused);
  void initialize(WindowComponent& w);
  void destruct(WindowComponent& w);
  std::vector<WindowComponent*> windows;
  GLFWwindow* mainContext;
};