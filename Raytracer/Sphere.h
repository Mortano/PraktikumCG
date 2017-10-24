#pragma once

#include <glm\common.hpp>
#include <tuple>

struct Ray;

struct Sphere {
  float radius;
  glm::vec3 center;
};

//! \brief Calculate the hit position and normal between the ray and the sphere.
//! If the ray does not hit the sphere, false is returned in the first tuple
//! element
std::tuple<bool, glm::vec3, glm::vec3> traceSphere(Ray &ray,
                                                   const Sphere &sphere);
