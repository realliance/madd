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
        void UpdateProjection();
        virtual void Update()=0;
        void LookAt(glm::vec3 pos);
        void SetPosition(glm::vec3 pos);
        void SetPitchAndYaw(float pitch, float yaw);
        void MovePosition(glm::vec3 movementVector);
    protected:
        Madd* context;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::mat4 view;
        glm::mat4 projection;
};

#endif //CAMERA_H