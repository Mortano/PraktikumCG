#pragma once
#include <glm\common.hpp>
#include <memory>

struct Ray;

//! \brief Primitive base class
struct Primitive {
  using Ptr = std::unique_ptr<Primitive>;

  virtual ~Primitive() {}

  virtual bool Intersects(Ray &ray, glm::vec3 *hitPos,
                          glm::vec3 *hitNormal) const = 0;
};
