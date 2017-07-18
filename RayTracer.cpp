
struct IntersectInfo {
  float t;
  glm::vec3 P;
  glm::vec3 normal;
};

void RayTracer::get_ray(int i, int j, glm::vec4& P1)
{
  float x = glm::tan(cam->fovx / 2) * ((float)i - width/2)/(width/2);
  float y = glm::tan(cam->fovy / 2) * (height/2 - (float)j) / (height/2);
  P1[0] = x;
  P1[1] = y;
  P1[2] = -1;
  P1[3] = 0;
}

int RayTracer::intersect(IntersectInfo& ret, glm::vec4& P0, glm::vec4& P1)
{
  float mint = -1.f;
  int has_intersect = 0;
  for(int k=0; k<scene.num_objects; k++)
  {
    Primitive *p = scene.objects[k];
    IntersectInfo inf = p->intersect(P0, P1);
    if(inf->t < mint && inf->t > 0)
    {
      has_intersect = 1;
      ret = inf;
      return 1;
    }
  }
  return 0;
}

RayTracer::find_color(IntersectInfo inf)
{
  glm::vec3 color = glm::vec3(0,0,0);
  glm::vec4 P0 = inf.P;
  glm::vec4 P1 = glm::vec4(0,0,0,0);
  float eps = 0.001;

  // shadow
  IntersectInfo dummy;
  for(int k=0; k<scene.num_lights; k++)
  {
    glm::vec4 PL = glm::normalize(scene.lights[k].pos - P0);
    if(!intersect(dummy, P0+eps*PL, PL))
    {
      // Get lighting
      color += glm::vec4(0.5, 0.1, 0.5, 1) * glm::dot(PL, inf.normal);
    }
  }
}
