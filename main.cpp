#include "RayTracer.h"
#include "Primitive.h"
#include "Scene.h"
#include "globals.h"
#include "camera.h"
#include "Sphere.h"
#include <iostream>
#include <FreeImage.h>
#include "Checkerboard.h"

Camera cam(6000, 60, 1.0, glm::vec3(0, 3, 8), glm::vec3(0,1.0,0), glm::vec3(0,1,0));
Scene scene;

int main(int argc, char* argv[])
{

  FreeImage_Initialise();
  glm::vec4 P1 = glm::vec4(-1, 2.25, -3, 1);
  //glm::vec4 P1 = glm::vec4(1,0,0, 1);
  glm::vec4 P2 = glm::vec4(1, 3.5, -1, 1);
  glm::vec4 P3 = glm::vec4(0.5, 4.25, -0.5, 1);

  Checkerboard ck(glm::vec4(0,1,0,1));
  scene.add_object(&ck);

  Sphere s1(1.0, P1);
  s1.material.reflectance = 0.60;
  s1.material.diffuse = 1.f*glm::vec4(0.5, 0.1, 0.1, 1);
  //s1.material.diffuse = 1.f*glm::vec4(0.5, 0.3, 0.0, 1);
  s1.material.shininess = 100.f;

  Sphere s2(0.15, P2);
  s2.material.reflectance = 0.45;
  s2.material.diffuse = glm::vec4(0.5, 0.1, 0.5, 1);
  s2.material.shininess = 100.f;

  Sphere s3(0.4, P3);
  s3.material.reflectance = (0.25);
  s3.material.diffuse = glm::vec4(0.1, 0.5, 0.2, 1);
  s3.material.shininess = 100.f;

  Sphere s4(10, glm::vec4(-5, 11.25, +100, 1));
  s4.material.reflectance = 0.15;
  s4.material.diffuse = 1.f*glm::vec4(0.5, 0.1, 0.1, 1);
  s4.material.shininess = 500.f;

  scene.add_object(&s1);
  scene.add_object(&s2);
  scene.add_object(&s3);
  //scene.add_object(&s4);
  Light l1, l2;
  l1.pos = 5.f*glm::vec4(20, 7, 8,1);
  l2.pos = 1.f*glm::vec4(-3, 7, -8, 1);
  scene.add_light(&l1);
  scene.add_light(&l2);
  std::cout << "Raytracer\n";
  RayTracer rt1;
  std::cout << "Raytracing..\n";
  rt1.ray_trace();
  std::cout << sizeof(unsigned char);
  FIBITMAP *img = FreeImage_ConvertFromRawBits(rt1.framebuffer, cam.width,
    cam.height, cam.width * 3, 3*sizeof(unsigned char)*8, 0xFF0000, 0x00FF00, 0x0000FF, true);

  std::cout << "Saving screenshot: " << "\n";

  FreeImage_Save(FIF_PNG, img, "testout.png", 0);
  FreeImage_Save(FIF_PNG, rt1.fi_buffer, "testout_fi.png", 0);
  return 0;
}
