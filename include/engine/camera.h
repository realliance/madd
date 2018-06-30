#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
class Madd;
class Camera{
    public:
        Camera(Madd* parent);
        ~Camera();
        glm::mat4* GetView();
        glm::mat4* GetProjection();
        void Update();
    private:
        glm::mat4 view;
        glm::mat4 projection;
        Madd* parent;
};

#endif //CAMERA_H