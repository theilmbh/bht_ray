#include "RayTracer.h"
#include "Primitive.h"
#include "Scene.h"
#include "globals.h"
#include "camera.h"
#include "Sphere.h"
#include <iostream>
#include <FreeImage.h>

Camera cam(1, glm::vec3(0, 0, 2), glm::vec3(0,0,0), glm::vec3(0,1,0));
Scene scene;

int main(int argc, char* argv[])
{
  FreeImage_Initialise();
  glm::vec4 P1 = glm::vec4(-1, 0, -3, 1);
  glm::vec4 P2 = glm::vec4(1, -0.5, -1, 1);
  glm::vec4 P3 = glm::vec4(0.5, -1.25, -0.5, 1);

  Sphere s1(1.0, P1);
  s1.reflectance = 0.65;
  s1.diffuse = 1.f*glm::vec4(0.5, 0.1, 0.1, 1);

  Sphere s2(0.15, P2);
  s2.reflectance = 0.25;
  s2.diffuse = glm::vec4(0.5, 0.1, 0.5, 1);

  Sphere s3(0.4, P3);
  s3.reflectance = (0.75);
  s3.diffuse = glm::vec4(0.1, 0.5, 0.2, 1);

  scene.add_object(&s1);
  scene.add_object(&s2);
  scene.add_object(&s3);

  Light l1, l2;
  l1.pos = 5.f*glm::vec4(20, 0, 8,1);
  l2.pos = 1.f*glm::vec4(-3, -3, -8, 1);
  scene.add_light(&l1);
  scene.add_light(&l2);

  RayTracer rt1;
  std::cout << "Raytracing..\n";
  rt1.ray_trace();
  std::cout << sizeof(unsigned char);
  FIBITMAP *img = FreeImage_ConvertFromRawBits(rt1.framebuffer, scene.width,
    scene.height, scene.width * 3, 3*sizeof(unsigned char)*8, 0xFF0000, 0x00FF00, 0x0000FF, true);

  std::cout << "Saving screenshot: " << "\n";

  FreeImage_Save(FIF_PNG, img, "testout.png", 0);
  FreeImage_Save(FIF_PNG, rt1.fi_buffer, "testout_fi.png", 0);
  return 0;
}
