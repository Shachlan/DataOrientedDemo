#pragma once

#include <memory>
#include <string>
#include <variant>

#include "BaseOO.hpp"

namespace OO::Static {

class Text {
 public:
  std::string_view text;
  std::vector<OO::Animation> animations;
  float x, y, red, green, blue, scale, opacity;
  Text makeCopy() const;

  UpdateOperator updateOperatorForProperty(Property property);
  float &propertyToUpdate(Property property);
};

class Image {
 public:
  std::vector<OO::Animation> animations;
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

}  // namespace OO::Static
