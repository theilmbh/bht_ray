#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm/glm.hpp>
#include <FreeImage.h>

#define MAX_REFLECT 10

struct MaterialProperties {
  glm::vec4 diffuse;
  float reflectance=0;
  float shininess=0;
  float index_of_refraction=1.0;
  float transmittance=0.0;
};

struct IntersectInfo {
  float t;
  glm::vec4 P;
  glm::vec4 ray;
  glm::vec4 normal;
  MaterialProperties material;
};



class RayTracer
{

public:

  int reflect_depth;
  int refract_depth;

  unsigned char *framebuffer;
  FIBITMAP* fi_buffer;

  RayTracer();
  ~RayTracer();

  void get_ray(int i, int j, glm::vec4& P1);
  void ray_trace();

  int intersect(IntersectInfo& ret, glm::vec4 P0, glm::vec4 P1);

  glm::vec4 find_color(IntersectInfo inf);
  glm::vec4 do_recursive_ray(glm::vec4 P0, glm::vec4 P1);
};

#endif
