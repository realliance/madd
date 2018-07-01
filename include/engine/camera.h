#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
class Madd;
class Camera{
    public:
        Camera(){}
        Camera(Madd* context);
        virtual ~Camera();
        virtual void Init(Madd* context);
        glm::mat4* GetView();
        glm::mat4* GetProjection();
        virtual void Update();
        virtual void SetPosition(glm::vec3 pos);
        virtual void MovePosition(glm::vec3 movementVector);
    private:
        glm::vec3 cameraPosition;
        glm::vec3 targetPosition;
        glm::vec3 upVector;
        glm::mat4 view;
        glm::mat4 projection;
        Madd* context;
};

#endif //CAMERA_H