#include "Primitive.h"

IntersectInfo Primitive::intersect(glm::vec4 P0, glm::vec4 P1)
{
  IntersectInfo ret;
  ret.t = -1;
  ret.P = glm::vec4(0,0,0,1);
  ret.normal = glm::vec4(0,0,0,0);

  return ret;
}
