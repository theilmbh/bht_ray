#ifndef SCENE_H
#define SCENE_H

#include "Primitive.h"
#include <iostream>
#include <glm/glm.hpp>

#define MAX_OBJECTS 10
#define MAX_LIGHTS 10

struct Light{
  glm::vec4 pos;
};

class Scene
{
public:
  int num_objects;
  int num_lights;

  int width = 4096;
  int height = 4096;

  glm::vec4 ambient = glm::vec4(0.07, 0.07, 0.07, 1);

  Primitive *objects[MAX_OBJECTS];
  Light *lights[MAX_LIGHTS];
  void add_object(Primitive *obj);
  void add_light(Light *l);
  Scene(){
    num_objects = 0;
    num_lights = 0;
  }
};



#endif
