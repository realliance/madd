#include "collidertypes/boxcollider.h"
#include "util.h"

#define x_v 0
#define y_v 1
#define z_v 2

BoxCollider::BoxCollider(std::vector<float>& vertices, int stride){
  origin = Util::VolumeCentroid(vertices, stride);
  minBox = Util::MinBoundingBox(vertices, stride, origin);
  maxBox = Util::MaxBoundingBox(vertices, stride, origin);
}

#undef x_v
#undef y_v
#undef z_v
