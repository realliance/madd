#include "collidertypes/spherecollider.h"
#include "util.h"

SphereCollider::SphereCollider(std::vector<float>& vertices, int stride){
  origin = Util::VolumeCentroid(vertices, stride);
  radius = Util::MaxRadius(vertices, stride, origin);
}
