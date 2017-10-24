#pragma once
#include <glm\common.hpp>

struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;
  float t;
};
