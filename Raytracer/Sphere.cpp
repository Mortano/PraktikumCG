#include "Sphere.h"

#include "Ray.h"

#include <glm\geometric.hpp>

std::tuple<bool, glm::vec3, glm::vec3> traceSphere(Ray &ray,
                                                   const Sphere &sphere) {
  auto rSqr = sphere.radius * sphere.radius;
  auto co = sphere.center - ray.origin;

  auto tca = glm::dot(co, ray.direction);
  auto coSqr = glm::dot(co, co);
  auto dSqr = coSqr - tca * tca;

  if (dSqr > rSqr)
    return std::make_tuple(false, glm::vec3{}, glm::vec3{});

  auto thc = sqrtf(rSqr - coSqr + tca * tca);
  auto t0 = tca - thc;
  auto t1 = tca + thc;

  if (t0 >= ray.t)
    return std::make_tuple(false, glm::vec3{}, glm::vec3{}); // Not close enough
  if (t0 < 0) {                // First intersection is behind ray origin
    if (t1 < 0 || t1 >= ray.t) // Second intersection is also behind ray origin,
                               // or behind closer intersection
      return std::make_tuple(false, glm::vec3{}, glm::vec3{});
    // t1 is a hit point!
    ray.t = t1;
    auto hitPoint = ray.origin + (ray.direction * t1);
    auto hitNormal = glm::normalize(hitPoint - sphere.center);
    return std::make_tuple(true, hitPoint, hitNormal);
  }
  // t0 is a hit point
  ray.t = t0;
  auto hitPoint = ray.origin + (ray.direction * t0);
  auto hitNormal = glm::normalize(hitPoint - sphere.center);
  return std::make_tuple(true, hitPoint, hitNormal);
}
