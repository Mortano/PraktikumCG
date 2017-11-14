#include "Light.h"

PointLight::PointLight(const pe::RGB_32BitFloat &intensity,
                       const glm::vec3 &position)
    : _position(position), _intensity(intensity) {}

glm::vec3 PointLight::GetPosition() const { return _position; }

glm::vec3 PointLight::GetDirection() const { return {}; }

bool PointLight::HasPosition() const { return true; }

pe::RGB_32BitFloat PointLight::Intensity() const { return _intensity; }
