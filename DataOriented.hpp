#pragma once

#include <gsl/span>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

#include "Enums.hpp"
#include "Interpolator.hpp"

namespace DataOriented {

struct InputValue {
  float initialValue;

  gsl::span<LinearInterpolator> animations;

  UpdateOperator updateOperator;
};

class Text {
 public:
  Text(const std::string_view &text, gsl::span<float, 7> properties)
      : text(text), properties(properties) {}
  std::string_view text;
  gsl::span<float, 7> properties;

  UpdateOperator updateOperatorForProperty(Property property);
};

class Image {
 public:
  Image(const std::string_view &imageSource, gsl::span<float, 4> properties)
      : imageSource(imageSource), properties(properties) {}
  std::string_view imageSource;
  gsl::span<float, 4> properties;

  UpdateOperator updateOperatorForProperty(Property property);
};

using Model = std::variant<Image, Text>;

struct Input {
  std::vector<Model> models;
  std::vector<InputValue> inputValues;
  std::vector<LinearInterpolator> interpolators;
  std::vector<float> interpolationResults;
};

void interpolateModels(const std::vector<InputValue> &sourceValues,
                       std::vector<float> &properties, float time);

}  // namespace DataOriented
