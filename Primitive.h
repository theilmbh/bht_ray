#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "RayTracer.h"
#include <glm/glm.hpp>

class Primitive
{
public:
  glm::mat4 xform;

  Primitive(){
    xform = glm::mat4(1.0);
  };
  ~Primitive() {};

  virtual IntersectInfo intersect(glm::vec4 P0, glm::vec4 P1);
};


#endif
