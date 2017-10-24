#include "Sphere.h"
#include "Util.h"
#include "kamera.h"
#include <string>
#include <vector>

int main(int argc, char **argv) {
  // 3 steps:
  // 1) set up the scene (spheres, triangles, colors etc.)
  // 2) trace the rays
  // 3) output the image
  Sphere sphere;
  sphere.radius = 2;
  sphere.center = {0, 0, 5};

  Kamera cam;
  cam.brennweite = 90.f * 0.0174533f;
  cam.transformation = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

  const int width = 512;
  const int height = 512;

  std::vector<uint32_t> pixels;
  pixels.resize(width * height);

  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto ray = cam.rayforpixel(x, y, width, height);
      auto hitResult = traceSphere(ray, sphere);

      auto wasHit = std::get<0>(hitResult);
      if (!wasHit)
        continue;

      auto &hitPos = std::get<1>(hitResult);
      auto &normal = std::get<2>(hitResult);

      auto cameraFwd = cam.getForward();
      cameraFwd *= -1;

      auto nDotl = glm::dot(normal, cameraFwd);
      auto greyscale = static_cast<uint32_t>(nDotl * 255);

      pixels[y * width + x] = fromRGBA(greyscale, greyscale, greyscale, 255);
    }
  }

  // Output as file
  dumpPPM(pixels, width, height, "D:\\raytraceDump.ppm");

  return 0;
}
