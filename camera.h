// camera header
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

const float deg_to_rad = 3.14159 / 180.0;

class Camera
{
public:
  int width, height;
  float fov, fovx, fovy, aspect;
  glm::vec3 pos;
  glm::vec3 up;
  glm::vec3 center;
  glm::mat4 cam_to_world;

  glm::mat4 getCameraViewMatrix();
  glm::mat4 getCameraProjectionMatrix();
  Camera(int resy, float fov, float aspect, glm::vec3 pos, glm::vec3 center, glm::vec3 up);
  ~Camera();
  void translate(float dist, glm::vec3 dir);
  void reshape(int x, int y);
  void update(float dt);
  float vx=0.f, vy=0.f, vz=0.f;
};
#endif
