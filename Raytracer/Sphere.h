#pragma once

#include "Primitive.h"
#include <glm\common.hpp>
#include <tuple>

struct Ray;

//! \brief Sphere primitive
struct Sphere : Primitive {

  //! \brief Compute intersection between ray and sphere
  bool Intersects(Ray &ray, glm::vec3 *hitPos,
                  glm::vec3 *hitNormal) const override;
  Color color() const override;
  Material material() const override;

  float radius;
  glm::vec3 center;
  Color xcolor;
  Material xmaterial;
};
