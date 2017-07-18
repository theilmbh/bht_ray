#ifndef SCENE_H
#define SCENE_H

#include "Primitive.h"

#define MAX_OBJECTS 10
#define MAX_LIGHTS 10

struct Light{

};

class Scene
{
public:
  int num_objects;
  int num_lights;

  Primitive objects[MAX_OBJECTS];
  Light lights[MAX_LIGHTS];
};

#endif
