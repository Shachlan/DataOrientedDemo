
#pragma once
#include <algorithm>

struct LinearInterpolator {
  float min, max;

  float interpolate(float time) const { return std::clamp(time, min, max); }
};
