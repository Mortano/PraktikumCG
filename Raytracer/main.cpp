#include "Light.h"
#include "Sphere.h"
#include "Util.h"
#include "kamera.h"
#include <algorithm>
#include <string>
#include <vector>

struct Scene {
  bool Intersects(Ray &ray, glm::vec3 *hitPos = nullptr,
                  glm::vec3 *hitNormal = nullptr) const {
    bool wasHit = false;
    for (auto &primitive : primitives) {
      wasHit |= primitive->Intersects(ray, hitPos, hitNormal);
    }
    return wasHit;
  }

  Kamera cam;
  std::vector<Primitive::Ptr> primitives;
  std::vector<Light::Ptr> lights;
};

static Scene BuildScene() {
  std::vector<Primitive::Ptr> primitives;

  auto sphere1 = std::make_unique<Sphere>();
  sphere1->radius = 2.f;
  sphere1->center = {0, 0, 5};

  auto sphere2 = std::make_unique<Sphere>();
  sphere2->radius = 10.f;
  sphere2->center = {0.f, 13.f, 5.f};

  auto sphere3 = std::make_unique<Sphere>();
  sphere3->radius = 0.25f;
  sphere3->center = {-1.f, 0, 2.5f};

  primitives.push_back(std::move(sphere1));
  primitives.push_back(std::move(sphere2));
  primitives.push_back(std::move(sphere3));

  std::vector<Light::Ptr> lights;

  auto lightColor = pe::RGB_32BitFloat{1.f, 1.f, 1.f};
  auto lightPosition = glm::vec3{0, 0, 0};
  auto light1 = std::make_unique<PointLight>(lightColor, lightPosition);
  lights.push_back(std::move(light1));

  // lightColor = {0.7f, 0.f, 0.f};
  // lightPosition = {-2.f, 0, 2.f};
  // auto light2 = std::make_unique<PointLight>(lightColor, lightPosition);
  // lights.push_back(std::move(light2));

  Kamera cam;
  cam.brennweite = 90.f * 0.0174533f;
  cam.transformation = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  return {cam, std::move(primitives), std::move(lights)};
}

static pe::RGB_32BitFloat ComputeRadiance(Ray &ray, const Scene &scene,
                                          uint32_t traceDepth) {
  glm::vec3 hitPos, hitNormal;
  if (!scene.Intersects(ray, &hitPos, &hitNormal))
    return {};

  pe::RGB_32BitFloat totalIntensity;

  for (auto &light : scene.lights) {
    // Calculate diffuse, specular etc.

    // Is light visible?
    auto toLight = glm::normalize(light->GetPosition() - hitPos);
    Ray shadowRay;
    shadowRay.direction = toLight;
    shadowRay.origin = hitPos + (shadowRay.direction * 0.001f);
    shadowRay.t = std::numeric_limits<float>::max();
    auto lightVisible = !scene.Intersects(shadowRay);
    if (!lightVisible)
      continue;

    // 1) Diffuse reflection
    auto nDotl = std::max(0.f, glm::dot(hitNormal, toLight));

    // 2) Specular reflection
    auto view = scene.cam.getForward() * -1.f;
    auto r = Reflect(toLight * -1.f, hitNormal);
    const auto Exponent = 20.f;
    auto rDotv = std::max(0.f, glm::dot(r, view));
    auto spec = (light->Intensity() * std::powf(rDotv, Exponent));

    totalIntensity += (light->Intensity() * nDotl); //+ spec
  }

  constexpr uint32_t MaxTraceDepth = 2;
  // 3) Real reflections
  if (traceDepth < MaxTraceDepth) {
    auto view = glm::normalize(hitPos - scene.cam.getPosition());
    auto reflectionVec = Reflect(view, hitNormal);

    auto vDotn = glm::dot(view * -1.f, hitNormal);

    Ray reflectionRay;
    reflectionRay.direction = reflectionVec;
    reflectionRay.origin = hitPos + (reflectionVec * 0.001f);
    reflectionRay.t = std::numeric_limits<float>::max();

    auto reflectedRadiance =
        ComputeRadiance(reflectionRay, scene, traceDepth + 1);
    totalIntensity += reflectedRadiance * vDotn;
  }

  return totalIntensity;
}

int main(int argc, char **argv) {
  // 3 steps:
  // 1) set up the scene (spheres, triangles, colors etc.)
  // 2) trace the rays
  // 3) output the image

  auto scene = BuildScene();

  const int width = 512;
  const int height = 512;

  std::vector<uint32_t> pixels;
  pixels.resize(width * height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto ray = scene.cam.rayforpixel(x, y, width, height);

      auto totalIntensity = ComputeRadiance(ray, scene, 1);

      auto r = static_cast<uint8_t>(std::min(1.f, totalIntensity.r()) * 255);
      auto g = static_cast<uint8_t>(std::min(1.f, totalIntensity.g()) * 255);
      auto b = static_cast<uint8_t>(std::min(1.f, totalIntensity.b()) * 255);

      pixels[y * width + x] = fromRGBA(r, g, b, 255);
    }
  }

  // Output as file
  dumpPPM(pixels, width, height, "D:\\raytraceDump.ppm");

  return 0;
}
