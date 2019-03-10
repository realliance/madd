#ifndef FREECAM_H
#define FREECAM_H
#include "camera.h"
#include <glm/glm.hpp>
class FreeCam : public Camera {
    public:
		FreeCam();
        ~FreeCam();
        void ProcessInput();
        void ProcessCursorPos(double xpos, double ypos);
        void Update();
        void ToggleMouseLock(int key=0, int action=1);
    private:
        bool mouseLocked;
        bool firstCursor;
        glm::vec2 lastCursor;
        float movementSpeed = 2.0f;
        float lookSpeed = 0.05f;
        float pitch;
        float yaw;
};

#endif //FREECAM_H
