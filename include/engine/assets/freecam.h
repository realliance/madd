#ifndef FREECAM_H
#define FREECAM_H
#include "camera.h"
#include <glm/glm.hpp>
class FreeCam :public Camera{
    public:
        FreeCam(Madd* context);
        ~FreeCam();
        void ProcessInput(int key, int action);
        void Update();
    private:
        glm::vec3 position;
};

#endif //FREECAM_H
