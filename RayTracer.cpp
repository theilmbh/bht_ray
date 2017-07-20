#include "RayTracer.h"
#include "Scene.h"
#include "globals.h"
#include "Primitive.h"
#include <iostream>
#include <FreeImage.h>

RayTracer::RayTracer()
{
  framebuffer = new unsigned char[scene.height*scene.width*3];
  fi_buffer = FreeImage_Allocate(scene.width, scene.height, 24);
  std::cout << scene.width << "\n";
}

RayTracer::~RayTracer()
{
  delete framebuffer;
}

void RayTracer::get_ray(int i, int j, glm::vec4& P1)
{
  int height = scene.height;
  int width = scene.width;
  float x = glm::tan(cam.fovx / 2) * ((float)i - width/2)/(width/2);
  float y = glm::tan(cam.fovy / 2) * (height/2 - (float)j) / (height/2);
  //std::cout << "x: " << i << " y: " << j << "\n";
  P1 = glm::normalize(glm::vec4(x, y, -1, 0)); // Need to transform to world coords

}

int RayTracer::intersect(IntersectInfo& ret, glm::vec4 P0, glm::vec4 P1)
{

  float mint = 1e9;
  int has_intersect = 0;
  for(int k=0; k<scene.num_objects; k++)
  {
    Primitive *p = scene.objects[k];
    IntersectInfo inf = p->intersect(P0, P1);
    //std::cout << inf.t << "\n";
    if(inf.t < mint && inf.t > 0)
    {
      //std::cout << "Intersect! " << inf.t << "\n";
      has_intersect = 1;
      ret = inf;
    }
  }
  return has_intersect;
}

glm::vec4 RayTracer::find_color(IntersectInfo inf)
{
  glm::vec4 color = glm::vec4(0,0,0,0);
  glm::vec4 P0 = inf.P; // intersect point
  glm::vec4 P1 = glm::vec4(0,0,0,0);
  float eps = 0.0001;

  glm::vec3 eyedirn = glm::normalize(cam.pos - glm::vec3(P0));
  // Ambient
  //color += scene.ambient;

  // Shadow Ray
  IntersectInfo dummy;
  for(int k=0; k<scene.num_lights; k++)
  {
    glm::vec4 PL = (scene.lights[k]->pos - P0);
    glm::vec3 lightdir = glm::normalize(glm::vec3(PL));
    glm::vec3 N = glm::normalize(glm::vec3(inf.normal));

    if(!intersect(dummy, P0+eps*PL, PL))
    {
      // Get lighting

      glm::vec3 halfv = glm::normalize(lightdir + eyedirn);
      color += inf.diffuse * glm::max(glm::dot(lightdir, N), 0.f);
      float s =  glm::pow(glm::max(glm::dot(halfv, N), 0.f), 1000);
      color += s*glm::vec4(1,1,1,1);

    }

    // Reflectance
    float reflectance = 0.5;
    glm::vec3 old_ray = glm::normalize(glm::vec3(inf.ray));
    if(reflect_depth < MAX_REFLECT)
    {
      reflect_depth++;
      //std::cout << reflect_depth << "\n";
      P1 = glm::vec4(glm::normalize(old_ray - 2.f*glm::dot(old_ray, N)*N), 0);
      color += inf.reflectance*do_recursive_ray(P0, P1);
    }

  }
  return color;
}

glm::vec4 RayTracer::do_recursive_ray(glm::vec4 P0, glm::vec4 P1)
{
  glm::vec4 color = glm::vec4(0,0,0,1);
  IntersectInfo d;
  if(intersect(d, P0, P1))
  {
    color = find_color(d);
  }
  return color;
}

void RayTracer::ray_trace()
{
  glm::vec4 ray;
  glm::vec4 color;
  RGBQUAD fi_color;
  glm::vec4 P0 = glm::vec4(cam.pos, 1);
  IntersectInfo d;


  for(int i = 0; i<scene.width; i++)
  {
    for(int j=0; j<scene.height; j++)
    {
      reflect_depth = 0;
      get_ray(i, j, ray);
      color = do_recursive_ray(P0, ray);
      // if(color[0] > 0){
      //   std::cout << (int)(color[0]*255) << " "
      //     << (int)(color[1]*255) << " " << (int)(color[2]*255) << "\n";
      // }

      fi_color.rgbRed = glm::min((color[0]*255), 255.f);
      fi_color.rgbGreen = glm::min((color[1]*255), 255.f);
      fi_color.rgbBlue = glm::min((color[2]*255), 255.f);
      FreeImage_SetPixelColor(fi_buffer, i, j, &fi_color);
      // if(intersect(d, P0, ray))
      // {
      //   color = find_color(d);
      //   framebuffer[i*scene.width + j]= (unsigned char)(color[0]*255);
      //   framebuffer[i*scene.width + j+1]= (unsigned char)(color[1]*255);
      //   framebuffer[i*scene.width + j+2]= (unsigned char)(color[2]*255);
      //
      //   fi_color.rgbRed = glm::min((color[0]*255), 255.f);
      //   fi_color.rgbGreen = glm::min((color[1]*255), 255.f);
      //   fi_color.rgbBlue = glm::min((color[2]*255), 255.f);
      //   FreeImage_SetPixelColor(fi_buffer, i, j, &fi_color);
      //   // std::cout << (unsigned char)(color[0]*255) << " "
      //   // << (unsigned char)(color[1]*255) << " " << (unsigned char)(color[2]*255) << "\n";
      // }
    }
  }
}
