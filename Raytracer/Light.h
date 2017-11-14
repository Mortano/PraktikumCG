#pragma once

#include "peColor.h"
#include <glm\common.hpp>
#include <memory>

struct Light {
  using Ptr = std::unique_ptr<Light>;

  virtual ~Light() {}

  virtual glm::vec3 GetPosition() const = 0;
  virtual glm::vec3 GetDirection() const = 0;
  virtual bool HasPosition() const = 0;

  virtual pe::RGB_32BitFloat Intensity() const = 0;
};

struct PointLight : Light {

  PointLight(const pe::RGB_32BitFloat &intensity, const glm::vec3 &position);

  glm::vec3 GetPosition() const override;
  glm::vec3 GetDirection() const override;
  bool HasPosition() const override;
  pe::RGB_32BitFloat Intensity() const override;

private:
  pe::RGB_32BitFloat _intensity;
  glm::vec3 _position;
};
