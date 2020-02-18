#include <cassert>
#include <chrono>
#include <cstdlib>

#include "DataOriented.hpp"
#include "StaticOO.hpp"
#include "StaticWithSpan.hpp"
#include "VirtualOO.hpp"

namespace {
static constexpr auto kNumberOfModels = 100000;
static constexpr auto kNumberOfAnimationsPerModel = 100;
static constexpr auto kTotalNumberOfAnimations =
    kNumberOfModels * kNumberOfAnimationsPerModel;

inline int randomValue(int maxValue) { return rand() % maxValue; }

const std::vector<std::string> kStrings = {"foo", "bar", "baz",
                                           "some other string"};

auto makeInterpolator() {
  return LinearInterpolator{(float)(rand() % 256 - 256), (float)(rand() % 256)};
}

void makeAnimations(const std::vector<Property> &properties,
                    std::vector<OO::Animation> &animations, size_t index) {
  auto remainingAnimations = kNumberOfAnimationsPerModel;
  size_t count = 0;
  for (size_t j = 0; j < properties.size(); ++j) {
    auto property = properties[j];
    if (remainingAnimations == 0) {
      return;
    }
    auto currentAnimations = j == properties.size() - 1
                                 ? remainingAnimations
                                 : rand() % remainingAnimations;
    remainingAnimations -= currentAnimations;
    for (int i = 0; i < currentAnimations; ++i) {
      animations[index + count] = OO::Animation{makeInterpolator(), {property}};
      ++count;
    }
  }
}

auto makeAnimations(const std::vector<Property> &properties) {
  auto animations = std::vector<OO::Animation>(kNumberOfAnimationsPerModel);
  makeAnimations(properties, animations, 0);
  return animations;
}

std::unique_ptr<OO::Virtual::Model> makeVirtualModel() {
  if (rand() % 2 == 0) {
    auto model = std::make_unique<OO::Virtual::Text>();
    model->text = kStrings[rand() % kStrings.size()];
    model->x = rand() % 100;
    model->y = rand() % 100;
    model->red = rand() % 256;
    model->green = rand() % 256;
    model->blue = rand() % 256;
    model->scale = rand() % 100;
    model->opacity = rand() % 100;
    model->animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  } else {
    auto model = std::make_unique<OO::Virtual::Image>();
    model->imageSource = kStrings[rand() % kStrings.size()];
    model->x = rand() % 100;
    model->y = rand() % 100;
    model->scale = rand() % 100;
    model->opacity = rand() % 100;
    model->animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  }
}

OO::Static::Model makeStaticModel() {
  if (rand() % 2 == 0) {
    auto model = OO::Static::Text();
    model.text = kStrings[rand() % kStrings.size()];
    model.x = rand() % 100;
    model.y = rand() % 100;
    model.red = rand() % 256;
    model.green = rand() % 256;
    model.blue = rand() % 256;
    model.scale = rand() % 100;
    model.opacity = rand() % 100;
    model.animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  } else {
    auto model = OO::Static::Image();
    model.imageSource = kStrings[rand() % kStrings.size()];
    model.x = rand() % 100;
    model.y = rand() % 100;
    model.scale = rand() % 100;
    model.opacity = rand() % 100;
    model.animations = makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity});
    return model;
  }
}

OO::StaticWithSpan::Model makeStaticModelWithSpan(
    std::vector<OO::Animation> &animations, size_t lastIndex) {
  if (rand() % 2 == 0) {
    auto model = OO::StaticWithSpan::Text();
    model.text = kStrings[rand() % kStrings.size()];
    model.x = rand() % 100;
    model.y = rand() % 100;
    model.red = rand() % 256;
    model.green = rand() % 256;
    model.blue = rand() % 256;
    model.scale = rand() % 100;
    model.opacity = rand() % 100;
    makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity},
        animations, lastIndex);
    model.animations =
        gsl::span(animations.data() + lastIndex, kNumberOfAnimationsPerModel);
    return model;
  } else {
    auto model = OO::StaticWithSpan::Image();
    model.imageSource = kStrings[rand() % kStrings.size()];
    model.x = rand() % 100;
    model.y = rand() % 100;
    model.scale = rand() % 100;
    model.opacity = rand() % 100;
    makeAnimations(
        {Property::X, Property::Y, Property::Scale, Property::Opacity},
        animations, lastIndex);
    model.animations =
        gsl::span(animations.data() + lastIndex, kNumberOfAnimationsPerModel);
    return model;
  }
}

void makeModels(std::vector<std::unique_ptr<OO::Virtual::Model>> &virtualModels,
                std::vector<OO::Static::Model> &staticModels,
                OO::StaticWithSpan::Input &staticWithSpanInput,
                DataOriented::Input &dataOrientedInput) {
  virtualModels.reserve(kNumberOfModels);
  staticModels.reserve(kNumberOfModels);
  staticWithSpanInput.models.reserve(kNumberOfModels);
  staticWithSpanInput.animations.reserve(kNumberOfAnimationsPerModel);
  dataOrientedInput.models.reserve(kNumberOfModels);
  dataOrientedInput.inputValues = std::vector<InputValue>(kNumberOfModels * 7);
  dataOrientedInput.interpolators.reserve(kNumberOfAnimationsPerModel);
  dataOrientedInput.interpolationResults =
      std::vector<float>(kNumberOfModels * 7);

  for (int i = 0; i < kNumberOfAnimationsPerModel; ++i) {
    dataOrientedInput.interpolators.push_back(makeInterpolator());
  }

  int totalSetProperties = 0;
  for (int i = 0; i < kNumberOfModels; ++i) {
    int numberOfProperties = 0;
    if (rand() % 2 == 0) {
      numberOfProperties = 7;
      auto virtualModel = std::make_unique<OO::Virtual::Text>();
      virtualModel->text = kStrings[rand() % kStrings.size()];
      virtualModel->x = rand() % 100;
      virtualModel->y = rand() % 100;
      virtualModel->red = rand() % 256;
      virtualModel->green = rand() % 256;
      virtualModel->blue = rand() % 256;
      virtualModel->scale = rand() % 100;
      virtualModel->opacity = rand() % 100;

      auto staticModel = OO::Static::Text();
      staticModel.text = virtualModel->text;
      staticModel.x = virtualModel->x;
      staticModel.y = virtualModel->y;
      staticModel.red = virtualModel->red;
      staticModel.green = virtualModel->green;
      staticModel.blue = virtualModel->blue;
      staticModel.scale = virtualModel->scale;
      staticModel.opacity = virtualModel->opacity;

      auto staticWithSpanModel = OO::StaticWithSpan::Text();
      staticWithSpanModel.text = virtualModel->text;
      staticWithSpanModel.x = virtualModel->x;
      staticWithSpanModel.y = virtualModel->y;
      staticWithSpanModel.red = virtualModel->red;
      staticWithSpanModel.green = virtualModel->green;
      staticWithSpanModel.blue = virtualModel->blue;
      staticWithSpanModel.scale = virtualModel->scale;
      staticWithSpanModel.opacity = virtualModel->opacity;

      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->x;
      dataOrientedInput.inputValues.back().updateOperator = UpdateOperator::Add;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->y;
      dataOrientedInput.inputValues.back().updateOperator = UpdateOperator::Add;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->red;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Multiply;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->blue;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Multiply;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->green;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Multiply;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->scale;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Multiply;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->opacity;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Replace;
      auto dataOrientedModel = DataOriented::Text(
          virtualModel->text,
          gsl::span(dataOrientedInput.interpolationResults.data() +
                        totalSetProperties,
                    numberOfProperties));
    } else {
      numberOfProperties = 4;
      auto virtualModel = std::make_unique<OO::Virtual::Image>();
      virtualModel->imageSource = kStrings[rand() % kStrings.size()];
      virtualModel->x = rand() % 100;
      virtualModel->y = rand() % 100;
      virtualModel->scale = rand() % 100;
      virtualModel->opacity = rand() % 100;

      auto staticModel = OO::Static::Image();
      staticModel.imageSource = virtualModel->imageSource;
      staticModel.x = virtualModel->x;
      staticModel.y = virtualModel->y;
      staticModel.scale = virtualModel->scale;
      staticModel.opacity = virtualModel->opacity;

      auto staticWithSpanModel = OO::StaticWithSpan::Image();
      staticWithSpanModel.imageSource = virtualModel->imageSource;
      staticWithSpanModel.x = virtualModel->x;
      staticWithSpanModel.y = virtualModel->y;
      staticWithSpanModel.scale = virtualModel->scale;
      staticWithSpanModel.opacity = virtualModel->opacity;

      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->x;
      dataOrientedInput.inputValues.back().updateOperator = UpdateOperator::Add;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->y;
      dataOrientedInput.inputValues.back().updateOperator = UpdateOperator::Add;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->scale;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Replace;
      dataOrientedInput.inputValues.push_back({});
      dataOrientedInput.inputValues.back().initialValue = virtualModel->opacity;
      dataOrientedInput.inputValues.back().updateOperator =
          UpdateOperator::Replace;
      auto dataOrientedModel = DataOriented::Image(
          virtualModel->imageSource,
          gsl::span(dataOrientedInput.interpolationResults.data() +
                        totalSetProperties,
                    numberOfProperties));
    }

    totalSetProperties += numberOfProperties;
  }
}

void testBunched() {
  auto start = std::chrono::steady_clock::now();
  auto virtualInputs =
      std::vector<std::unique_ptr<OO::Virtual::Model>>(kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    virtualInputs[i] = makeVirtualModel();
  }
  auto finish = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  printf("Time to allocate virtual: %f\n", elapsed.count());

  start = std::chrono::steady_clock::now();
  auto staticInputs = std::vector<OO::Static::Model>(kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    staticInputs[i] = makeStaticModel();
  }
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Time to allocate static: %f\n", elapsed.count());

  start = std::chrono::steady_clock::now();
  auto staticWithSpanInputs =
      std::vector<OO::StaticWithSpan::Model>(kNumberOfModels);
  auto animations =
      std::vector<OO::Animation>(kNumberOfAnimationsPerModel * kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    staticWithSpanInputs[i] =
        makeStaticModelWithSpan(animations, i * kNumberOfAnimationsPerModel);
  }
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Time to allocate static with span: %f\n", elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedVirtualModels =
      OO::Virtual::interpolateModels(virtualInputs, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Virtual: %lu took time: %f\n", interpolatedVirtualModels.size(),
         elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedStaticModels =
      OO::Static::interpolateModels(staticInputs, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Static: %lu took time: %f\n", interpolatedStaticModels.size(),
         elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedStaticWithSpanModels =
      OO::StaticWithSpan::interpolateModels(staticWithSpanInputs, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Static with span: %lu took time: %f\n",
         interpolatedStaticWithSpanModels.size(), elapsed.count());
}

void testInterleaved() {}

}  // namespace

int main(int argc, char *argv[]) {
  testBunched();

  testInterleaved();
}
