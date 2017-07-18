#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RayTracer.h"
#include <glm/glm.hpp>

class Primitive
{
public:
  Primitive();
  ~Primitive();

  virtual IntersectInfo intersect(glm::vec4 P0, glm::vec4 P1);
};

IntersectInfo Primitive::intersect(glm::vec4 P0, glm::vec4 P1)
{
  IntersectInfo ret;
  ret.t = -1;
  ret.P = glm::vec4(0,0,0,0);
  ret.normal = glm::vec4(0,0,0,0);

  return ret;
}

#endif
