#include <cassert>
#include <chrono>
#include <cstdlib>

#include "StaticOO.hpp"
#include "VirtualOO.hpp"

namespace {
static constexpr auto kNumberOfModels = 1000;
static constexpr auto kNumberOfAnimationsPerModel = 100;

const std::vector<std::string> kStrings = {"foo", "bar", "baz",
                                           "some other string"};

auto makeInterpolator() {
  return LinearInterpolator{(float)(rand() % 256 - 256), (float)(rand() % 256)};
}

auto makeAnimations(std::vector<Property> properties) {
  auto animations = std::vector<OO::Animation>();
  auto remainingAnimations = kNumberOfAnimationsPerModel;
  for (size_t j = 0; j < properties.size(); ++j) {
    auto property = properties[j];
    if (remainingAnimations == 0) {
      return animations;
    }
    auto currentAnimations = j == properties.size() - 1
                                 ? remainingAnimations
                                 : rand() % remainingAnimations;
    remainingAnimations -= currentAnimations;
    for (int i = 0; i < currentAnimations; ++i) {
      auto animation = OO::Animation{makeInterpolator(), {property}};
      animations.emplace_back(animation);
    }
  }
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

void testBunched() {
  auto virtualInputs =
      std::vector<std::unique_ptr<OO::Virtual::Model>>(kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    virtualInputs[i] = makeVirtualModel();
    for (int j = 0; j < kNumberOfAnimationsPerModel; ++j) {
    }
  }

  auto staticInputs = std::vector<OO::Static::Model>(kNumberOfModels);
  for (int i = 0; i < kNumberOfModels; ++i) {
    staticInputs[i] = makeStaticModel();
    for (int j = 0; j < kNumberOfAnimationsPerModel; ++j) {
    }
  }

  auto start = std::chrono::steady_clock::now();
  auto interpolatedVirtualModels =
      OO::Virtual::interpolateModels(virtualInputs, 2);
  auto finish = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  printf("size of result: %lu took time: %f\n",
         interpolatedVirtualModels.size(), elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedStaticModels =
      OO::Static::interpolateModels(staticInputs, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("size of result: %lu took time: %f\n", interpolatedStaticModels.size(),
         elapsed.count());
}

void testInterleaved() {}

}  // namespace

int main(int argc, char *argv[]) {
  testBunched();

  testInterleaved();
}
