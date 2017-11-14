#include "Sphere.h"

#include "Ray.h"

#include <glm\geometric.hpp>

bool Sphere::Intersects(Ray &ray, glm::vec3 *hitPos,
                        glm::vec3 *hitNormal) const {
  auto rSqr = radius * radius;
  auto co = center - ray.origin;

  auto tca = glm::dot(co, ray.direction);
  auto coSqr = glm::dot(co, co);
  auto dSqr = coSqr - tca * tca;

  if (dSqr > rSqr)
    return false;

  auto thc = sqrtf(rSqr - coSqr + tca * tca);
  auto t0 = tca - thc;
  auto t1 = tca + thc;

  if (t0 >= ray.t)
    return false;              // Not close enough
  if (t0 < 0) {                // First intersection is behind ray origin
    if (t1 < 0 || t1 >= ray.t) // Second intersection is also behind ray origin,
                               // or behind closer intersection
      return false;
    // t1 is a hit point!
    ray.t = t1;
    if (hitPos)
      *hitPos = ray.origin + (ray.direction * t1);
    if (hitNormal)
      *hitNormal = glm::normalize((ray.origin + (ray.direction * t1)) - center);
    return true;
  }
  // t0 is a hit point
  ray.t = t0;
  if (hitPos)
    *hitPos = ray.origin + (ray.direction * t0);
  if (hitNormal)
    *hitNormal = glm::normalize((ray.origin + (ray.direction * t0)) - center);
  return true;
}
