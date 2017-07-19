#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"
#include "RayTracer.h"

class Sphere : public Primitive
{
public:
  Sphere(float radius, glm::vec4 center){
    r = radius;
    C = center;
  };
  ~Sphere() {};

  float r;

  glm::vec4 C;
  IntersectInfo intersect(glm::vec4 P0, glm::vec4 P1);
};

IntersectInfo Sphere::intersect(glm::vec4 P0, glm::vec4 P1)
{
  IntersectInfo ret;
  float a = glm::dot(P1, P1);
  float b = 2*glm::dot(P0 - C, P1);
  float c = glm::dot(P0, P0) - 2*glm::dot(P0, C) + glm::dot(C, C) - r*r;

  float descrim = b*b-4*a*c;
  if(descrim < 0)
  {
    // No intersection
    ret.t = -1.f;
    ret.P = glm::vec4(0,0,0,1);
    ret.normal = glm::vec4(0,0,0,1);
    return ret;
  }
  float r1 = (-b + glm::sqrt(descrim))/(2*a);
  float r2 = (-b - glm::sqrt(descrim))/(2*a);

  float t_intersect = glm::min(r1, r2);
  ret.t = t_intersect;
  ret.P = P0 + P1*t_intersect;
  ret.normal = glm::normalize(ret.P - C);
  ret.ray = P1;
  ret.reflectance = reflectance;
  ret.diffuse = diffuse;
  return ret;
}
#endif
