#include "kamera.h"
#include "Util.h"
#include <cmath>

Ray Kamera::rayforpixel(int x, int y, int width, int height) {
  auto tanFov = tanf(brennweite / 2);
  auto aspect = height / static_cast<float>(width);

  auto cx = aspect * ((x * 2.f / width) - 1.f) * tanFov;
  auto cy = ((y * 2.f / height) - 1.f) * tanFov;

  auto fwd = asVec3(transformation[2]);
  auto right = asVec3(transformation[0]);
  auto up = asVec3(transformation[1]);
  auto pos = asVec3(transformation[3]);

  Ray ret;
  ret.origin = pos + fwd + right * cx + up * cy;
  ret.direction = glm::normalize(ret.origin - pos);
  ret.t = FLT_MAX;
  return ret;
}

glm::vec3 Kamera::getForward() const { return asVec3(transformation[2]); }

glm::vec3 Kamera::getPosition() const { return asVec3(transformation[3]); }
