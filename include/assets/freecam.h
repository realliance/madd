#ifndef FREECAM_H
#define FREECAM_H
#include "camera.h"
#include <glm/glm.hpp>
#include "components/cameracomponent.h"
#include "assets/freecamcomponent.h"
class FreeCam {
    public:
        static FreecamComponent Construct();
        static void Destruct(FreecamComponent& c);
        static void ProcessInput(FreecamComponent& c);
        static void ProcessCursorPos(FreecamComponent& c, double xpos, double ypos);
        static void Update(FreecamComponent& c);
        static void ToggleMouseLock(FreecamComponent& c, int key=0, int action=1);
};

#endif //FREECAM_H
