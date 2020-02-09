#pragma once

#include <memory>
#include <string>

#include "BaseOO.hpp"

namespace OO::Virtual {

class Model {
 public:
  virtual ~Model() = default;
  std::vector<OO::Animation> animations;
  void updateValue(Property property, float value) {
    auto op = updateOperatorForProperty(property);
    auto &currentValue = propertyToUpdate(property);
    currentValue = composeValue(currentValue, op, value);
  }
  virtual std::unique_ptr<Model> makeCopy() const = 0;

 protected:
  virtual UpdateOperator updateOperatorForProperty(Property property) = 0;
  virtual float &propertyToUpdate(Property property) = 0;
};

class Text : public Model {
 public:
  std::string_view text;
  float x, y, red, green, blue, scale, opacity;
  std::unique_ptr<Model> makeCopy() const override;

 protected:
  UpdateOperator updateOperatorForProperty(Property property) override;
  float &propertyToUpdate(Property property) override;
};

class Image : public Model {
 public:
  std::string_view imageSource;
  float x, y, scale, opacity;
  std::unique_ptr<Model> makeCopy() const override;

 protected:
  UpdateOperator updateOperatorForProperty(Property property) override;
  float &propertyToUpdate(Property property) override;
};

std::vector<std::unique_ptr<Model>> interpolateModels(
    const std::vector<std::unique_ptr<Model>> &inputs, float time);

}  // namespace OO::Virtual
