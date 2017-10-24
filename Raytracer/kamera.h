#pragma once

#include "Ray.h"
#include <glm\mat4x4.hpp>

struct Kamera {
  glm::mat4 transformation;
  float brennweite;

  Ray rayforpixel(int x, int y, int width, int height);
  glm::vec3 getForward() const;
};
