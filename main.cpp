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
  glm::vec4 P2 = glm::vec4(-0.8, 0.5, -1, 1);
  Sphere s1(1.0, P1);
  Sphere s2(0.15, P2);
  scene.add_object(&s1);
  scene.add_object(&s2);
  Light l1;
  l1.pos = 3.f*(P2-P1) + P1 ;
  l1.pos = glm::vec4(20, 0, 8,1);
  scene.add_light(&l1);

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
