#include "Scene.h"

void Scene::add_object(Primitive *obj)
{
  if(num_objects >= MAX_OBJECTS)
  {
    std::cout << "Too many objects\n";
    return;
  }

  objects[num_objects] = obj;
  num_objects++;
}

void Scene::add_light(Light *l)
{
  if(num_lights >= MAX_LIGHTS)
  {
    std::cout << "Too many lights\n";
    return;
  }

  lights[num_lights] = l;
  num_lights++;
}
