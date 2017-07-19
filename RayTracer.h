#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <FreeImage.h>

#define MAX_REFLECT 6

struct IntersectInfo {
  float t;
  float reflectance;
  glm::vec4 P;
  glm::vec4 ray;
  glm::vec4 normal;
  glm::vec4 diffuse;
};

class RayTracer
{

public:
  unsigned char *framebuffer;
  FIBITMAP* fi_buffer;

  RayTracer();
  ~RayTracer();

  int reflect_depth;
  int refract_depth;
  void get_ray(int i, int j, glm::vec4& P1);
  int intersect(IntersectInfo& ret, glm::vec4 P0, glm::vec4 P1);
  glm::vec4 find_color(IntersectInfo inf);
  void ray_trace();
  glm::vec4 do_recursive_ray(glm::vec4 P0, glm::vec4 P1);
};

#endif
