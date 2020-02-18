#pragma once

#include <gsl/span>
#include <memory>
#include <string>
#include <variant>

#include "BaseOO.hpp"

namespace OO::StaticWithSpan {

class Text {
 public:
  gsl::span<OO::Animation> animations;
  std::string_view text;
  float x, y, red, green, blue, scale, opacity;
  Text makeCopy() const;

  UpdateOperator updateOperatorForProperty(Property property);
  float &propertyToUpdate(Property property);
};

class Image {
 public:
  gsl::span<OO::Animation> animations;
  std::string_view imageSource;
  float x, y, scale, opacity;
  Image makeCopy() const;

  UpdateOperator updateOperatorForProperty(Property property);
  float &propertyToUpdate(Property property);
};

using Model = std::variant<Image, Text>;

std::vector<Model> interpolateModels(const std::vector<Model> &inputs,
                                     float time);

void updateValue(Model &model, Property property, float value);

struct Input {
  std::vector<Model> models;
  std::vector<OO::Animation> animations;
};

}  // namespace OO::StaticWithSpan
