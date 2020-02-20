#include <chrono>
#include <cstdlib>

#include "TediousStuff.hpp"

namespace {

// auto makeInterpolator() {
//   return LinearInterpolator{(float)(rand() % 256 - 256), (float)(rand() %
//   256)};
// }

// void makeAnimations(const std::vector<Property> &properties,
//                     std::vector<OO::Animation> &animations, size_t index) {
//   auto remainingAnimations = kNumberOfAnimationsPerModel;
//   size_t count = 0;
//   for (size_t j = 0; j < properties.size(); ++j) {
//     auto property = properties[j];
//     if (remainingAnimations == 0) {
//       return;
//     }
//     auto currentAnimations = j == properties.size() - 1
//                                  ? remainingAnimations
//                                  : rand() % remainingAnimations;
//     remainingAnimations -= currentAnimations;
//     for (int i = 0; i < currentAnimations; ++i) {
//       animations[index + count] = OO::Animation{makeInterpolator(),
//       {property}};
//       ++count;
//     }
//   }
// }

// auto makeAnimations(const std::vector<Property> &properties) {
//   auto animations = std::vector<OO::Animation>(kNumberOfAnimationsPerModel);
//   makeAnimations(properties, animations, 0);
//   return animations;
// }

// std::unique_ptr<OO::Virtual::Model> makeVirtualModel() {
//   if (rand() % 2 == 0) {
//     auto model = std::make_unique<OO::Virtual::Text>();
//     model->text = kStrings[rand() % kStrings.size()];
//     model->x = rand() % 100;
//     model->y = rand() % 100;
//     model->red = rand() % 256;
//     model->green = rand() % 256;
//     model->blue = rand() % 256;
//     model->scale = rand() % 100;
//     model->opacity = rand() % 100;
//     model->animations = makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity});
//     return model;
//   } else {
//     auto model = std::make_unique<OO::Virtual::Image>();
//     model->imageSource = kStrings[rand() % kStrings.size()];
//     model->x = rand() % 100;
//     model->y = rand() % 100;
//     model->scale = rand() % 100;
//     model->opacity = rand() % 100;
//     model->animations = makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity});
//     return model;
//   }
// }

// OO::Static::Model makeStaticModel() {
//   if (rand() % 2 == 0) {
//     auto model = OO::Static::Text();
//     model.text = kStrings[rand() % kStrings.size()];
//     model.x = rand() % 100;
//     model.y = rand() % 100;
//     model.red = rand() % 256;
//     model.green = rand() % 256;
//     model.blue = rand() % 256;
//     model.scale = rand() % 100;
//     model.opacity = rand() % 100;
//     model.animations = makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity});
//     return model;
//   } else {
//     auto model = OO::Static::Image();
//     model.imageSource = kStrings[rand() % kStrings.size()];
//     model.x = rand() % 100;
//     model.y = rand() % 100;
//     model.scale = rand() % 100;
//     model.opacity = rand() % 100;
//     model.animations = makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity});
//     return model;
//   }
// }

// OO::StaticWithSpan::Model makeStaticModelWithSpan(
//     std::vector<OO::Animation> &animations, size_t lastIndex) {
//   if (rand() % 2 == 0) {
//     auto model = OO::StaticWithSpan::Text();
//     model.text = kStrings[rand() % kStrings.size()];
//     model.x = rand() % 100;
//     model.y = rand() % 100;
//     model.red = rand() % 256;
//     model.green = rand() % 256;
//     model.blue = rand() % 256;
//     model.scale = rand() % 100;
//     model.opacity = rand() % 100;
//     makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity},
//         animations, lastIndex);
//     model.animations =
//         gsl::span(animations.data() + lastIndex,
//         kNumberOfAnimationsPerModel);
//     return model;
//   } else {
//     auto model = OO::StaticWithSpan::Image();
//     model.imageSource = kStrings[rand() % kStrings.size()];
//     model.x = rand() % 100;
//     model.y = rand() % 100;
//     model.scale = rand() % 100;
//     model.opacity = rand() % 100;
//     makeAnimations(
//         {Property::X, Property::Y, Property::Scale, Property::Opacity},
//         animations, lastIndex);
//     model.animations =
//         gsl::span(animations.data() + lastIndex,
//         kNumberOfAnimationsPerModel);
//     return model;
//   }
// }

void test() {
  auto start = std::chrono::steady_clock::now();
  std::vector<std::unique_ptr<OO::Virtual::Model>> virtualModels;
  std::vector<OO::Static::Model> staticModels;
  OO::StaticWithSpan::Input staticWithSpanInput;
  DataOriented::Input dataOrientedInput;
  Tedious::makeModels(virtualModels, staticModels, staticWithSpanInput,
                      dataOrientedInput);

  Tedious::verifyInitialModels(virtualModels, staticModels,
                               staticWithSpanInput.models,
                               dataOrientedInput.inputValues);

  auto finish = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = finish - start;
  printf("Time to allocate models: %f\n", elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedVirtualModels =
      OO::Virtual::interpolateModels(virtualModels, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Virtual: %lu took time: %f\n", interpolatedVirtualModels.size(),
         elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedStaticModels =
      OO::Static::interpolateModels(staticModels, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Static: %lu took time: %f\n", interpolatedStaticModels.size(),
         elapsed.count());

  start = std::chrono::steady_clock::now();
  auto interpolatedStaticWithSpanModels =
      OO::StaticWithSpan::interpolateModels(staticWithSpanInput.models, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Static with span: %lu took time: %f\n",
         interpolatedStaticWithSpanModels.size(), elapsed.count());

  start = std::chrono::steady_clock::now();
  DataOriented::interpolateModels(dataOrientedInput.inputValues,
                                  dataOrientedInput.interpolationResults, 2);
  finish = std::chrono::steady_clock::now();
  elapsed = finish - start;
  printf("Data oriented: took time: %f\n", elapsed.count());

  Tedious::verifyModels(interpolatedVirtualModels, interpolatedStaticModels,
                        interpolatedStaticWithSpanModels,
                        dataOrientedInput.interpolationResults);
}

}  // namespace

int main(int argc, char *argv[]) { test(); }
