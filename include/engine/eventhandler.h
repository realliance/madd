#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <functional>
#include <vector>
#include <unordered_map>
typedef std::function<void(int,int)> keyCB;

struct keyCallback;
struct GLFWwindow;
class Madd;
class EventHandler{
    public:
        EventHandler(Madd* context);
        ~EventHandler();
        void Update();
        void RegisterKeyCB(keyCB keyCBfunc, unsigned int keyCode, unsigned int keyMods=0);
        void RegisterMultipleKeyCB(keyCB keyCBfunc, std::vector<unsigned int> keyCode, unsigned int keyMods=0);
        void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void CBGen(void* func);
    private:
        Madd* context;
        std::unordered_map<int, std::vector<keyCallback>> keyboardCallbacks;
};

#endif //EVENTHANDLER_H