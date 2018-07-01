#ifndef FREECAM_H
#define FREECAM_H
#include "camera.h"
#include <glm/glm.hpp>
struct GLFWwindow;
class FreeCam :public Camera{
    public:
        FreeCam(Madd* context);
        ~FreeCam();
        void ProcessInput(int key, int action);
        void ProcessMousePosition(GLFWwindow* window, double xpos, double ypos);
        void Update();
    private:
        bool mouseLocked;
        glm::vec3 position;
};

#endif //FREECAM_H
