#include "collider.h"
#include <cmath>

Collider::Collider(EColliderShape shape, std::vector<float>& vertices, int stride){
    switch(shape){
        case box:
            CreateBoxCollisionShape(vertices, stride);
        break;
        case sphere:
            CreateSphereCollisionShape(vertices,stride);
        break;
    }
}

Collider::~Collider(){
    
}
#define x_v 0
#define y_v 1
#define z_v 2
void Collider::CreateBoxCollisionShape(std::vector<float>& vertices, int stride){
    btVector3 max;
    int length = vertices.size();
    for(int i = 0; i < length; i++){
        switch(i){
            case x_v:
                max.setX(vertices[i] > max.x() ? vertices[i] : max.x());
            break;
            case y_v:
                max.setY(vertices[i] > max.y() ? vertices[i] : max.y());
            break;
            case z_v:
                max.setZ(vertices[i] > max.z() ? vertices[i] : max.z());
            break;
            default:
                i += stride-2;
        }
    }
    shape = new btBoxShape(max);
}

void Collider::CreateSphereCollisionShape(std::vector<float>& vertices, int stride){
    float max {0};
    int length = vertices.size();
    for(int i = 0; i < length; i += stride){
        float temp = 0;
        temp += (vertices[x_v] * vertices[x_v]);
        temp += (vertices[y_v] * vertices[y_v]);
        temp += (vertices[z_v] * vertices[z_v]);
        max = max > temp ? max : temp;
    }
    max = sqrt(max);
    shape = new btSphereShape(max);
}
#undef x_v
#undef y_v
#undef z_v