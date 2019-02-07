#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <functional>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "keycodes.h"
struct keyCallback;
struct GLFWwindow;
class Madd;
typedef std::function<void(int,int)> keyCB;
typedef std::function<void(double,double)> cursorPosCB;
#define BIND(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2)
class EventHandler{
    public:
        void Init(Madd* context);
        static EventHandler& getInstance();
        static void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        void Update();
        void RegisterKeyCB(keyCB keyCBfunc, unsigned int keyCode, unsigned int keyMods=0);
        void RegisterMultipleKeyCB(keyCB keyCBfunc, std::vector<unsigned int> keyCode, unsigned int keyMods=0);
        void RegisterCursorPosCB(cursorPosCB cursorPosfunc);
        bool GetKeyDown(unsigned int key);
        glm::vec2 GetCursorPos();
        void LockCursor();
        void UnLockCursor();
        EventHandler(const EventHandler&) = delete;
        EventHandler& operator=(const EventHandler&) = delete;
    private:
		EventHandler();
        Madd* context;
        std::unordered_map<int, std::vector<keyCallback>> keyboardCallbacks;
        std::vector<cursorPosCB> cursorCallbacks;
};

#endif //EVENTHANDLER_H