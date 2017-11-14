#pragma once

#include <glm\common.hpp>
#include <glm\mat4x4.hpp>
#include <string>
#include <vector>

inline glm::vec3 asVec3(const glm::vec4 &vec) {
  return {vec[0], vec[1], vec[2]};
}

inline void dumpPPM(const std::vector<uint32_t> &pixels, int width, int height,
                    const std::string &path) {
  FILE *fp; /* b - binary mode */
  auto err = fopen_s(&fp, path.c_str(), "wb");
  (void)fprintf(fp, "P6\n%d %d\n255\n", width, height);
  for (auto &px : pixels) {
    fwrite(&px, 3, 1, fp);
  }
  fclose(fp);
}

inline uint32_t fromRGBA(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
  return r | (g << 8) | (b << 16) | (a << 24);
}

inline glm::vec3 Reflect(const glm::vec3 &dir, const glm::vec3 &normal) {
  auto dDotn = glm::dot(dir, normal);
  return dir - (2.f * dDotn * normal);
}
