#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <functional>
#include <vector>
#include <unordered_map>
#include "keycodes.h"
struct keyCallback;
struct GLFWwindow;
class Madd;
typedef std::function<void(int,int)> keyCB;
typedef std::function<void(double,double)> cursorPosCB;
#define BIND(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2)
class EventHandler{
    public:
        EventHandler(Madd* context);
        ~EventHandler();
        void Update();
        void RegisterKeyCB(keyCB keyCBfunc, unsigned int keyCode, unsigned int keyMods=0);
        void RegisterMultipleKeyCB(keyCB keyCBfunc, std::vector<unsigned int> keyCode, unsigned int keyMods=0);
        void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
        void CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        void RegisterCursorPosCB(cursorPosCB cursorPosfunc);
        unsigned int GetKey(unsigned int key);
        void GetCursorPos(double* xpos, double* ypos);
        void LockCursor();
        void UnLockCursor();
    private:
        Madd* context;
        std::unordered_map<int, std::vector<keyCallback>> keyboardCallbacks;
        std::vector<cursorPosCB> cursorCallbacks;
};

#endif //EVENTHANDLER_H