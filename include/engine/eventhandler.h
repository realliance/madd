#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H
#include <functional>
#include <vector>
#include <unordered_map>
typedef std::function<void(int,int)> keyCB;

struct keyCallback;
class Madd;
class EventHandler{
    public:
        EventHandler(Madd* context);
        ~EventHandler();
        void Update();
        void RegisterKeyCB(keyCB* keyCBfunc, unsigned int keyCode, unsigned int keyFlags);
    private:
        Madd* context;
        std::unordered_map<unsigned int, std::vector<keyCallback*>> keyboardCallbacks;
};

#endif //EVENTHANDLER_H