#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <FreeImage.h>

struct IntersectInfo {
  float t;
  glm::vec4 P;
  glm::vec4 normal;
};

class RayTracer
{

public:
  unsigned char *framebuffer;
  FIBITMAP* fi_buffer;

  RayTracer();
  ~RayTracer();

  void get_ray(int i, int j, glm::vec4& P1);
  int intersect(IntersectInfo& ret, glm::vec4 P0, glm::vec4 P1);
  glm::vec4 find_color(IntersectInfo inf);
  void ray_trace();
};

#endif
