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
        void SetPosition(float x, float y, float z);
        void MovePosition(float x, float y, float z);
    private:
        glm::mat4 view;
        glm::mat4 projection;
        Madd* context;
        double x,y,z;
};

#endif //CAMERA_H