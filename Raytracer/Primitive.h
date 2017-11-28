#pragma once
#include <glm\common.hpp>
#include <memory>

#include "peColor.h"

struct Ray;

//struct Color {
//	float rot;
//	float gruen;
//	float blau;
//};

using Color = pe::RGB_32BitFloat;

enum class Material
{
	Diffuse = 1 << 0,
	Specular = 1 << 1,
	DiffuseAndSpecular = Diffuse | Specular
};

inline bool IsDiffuse(Material mat)
{
	return (static_cast<int>(mat) & static_cast<int>(Material::Diffuse)) != 0;
}

inline bool IsSpecular(Material mat)
{
	return (static_cast<int>(mat) & static_cast<int>(Material::Specular)) != 0;
}

//! \brief Primitive base class
struct Primitive {
  using Ptr = std::unique_ptr<Primitive>;

  virtual ~Primitive() {}

  virtual bool Intersects(Ray &ray, glm::vec3 *hitPos,
                          glm::vec3 *hitNormal) const = 0;
  virtual Color color() const = 0;
  virtual Material material() const = 0;
	               
};
