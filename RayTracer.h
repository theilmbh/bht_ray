#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>

struct IntersectInfo {
  float t;
  glm::vec4 P;
  glm::vec4 normal;
};

class RayTracer
{

public:
  float *framebuffer;

  RayTracer();
  ~RayTracer();

  void get_ray(int i, int j, glm::vec4& P1);
  int intersect(IntersectInfo& ret, glm::vec4& P0, glm::vec4& P1);
  glm::vec3 find_color(IntersectInfo inf);
};

#endif
