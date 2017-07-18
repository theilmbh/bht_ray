// Camera
#include "camera.h"

Camera::Camera(float fov, glm::vec3 pos, glm::vec3 center, glm::vec3 up)
{
  this->fov = fov;
  this->pos = pos;
  this->center = center;
  this->up = up;
  this->aspect = 1.0;
}

Camera::~Camera()
{

}

glm::mat4 Camera::getCameraViewMatrix()
{

  glm::mat4 L = glm::lookAt(pos, center, up);
  return L;
}

glm::mat4 Camera::getCameraProjectionMatrix()
{
  glm::mat4 P = glm::perspective(glm::radians(fov), aspect, 0.1f, 1000.f);
  return P;
}

void Camera::translate(float dist, glm::vec3 dir)
{
  pos = pos + dist*glm::normalize(dir);
  center = center + dist*glm::normalize(dir);
}

void Camera::reshape(int x, int y)
{
  aspect = (float)x/ (float)y;
}

void Camera::update(float dt)
{
  pos += dt*vx*glm::normalize(glm::cross(pos-center, up));
  center += dt*vx*glm::normalize(glm::cross(pos-center, up));

  pos += dt*vy*glm::normalize(up);
  center += dt*vy*glm::normalize(up);

}
