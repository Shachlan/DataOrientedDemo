#include <chrono>
#include <cstdlib>

#include "TediousStuff.hpp"

namespace {

void test(int numberOfModels, int numberOfAnimationsPerModel,
          int numberOfRepetitions) {
  auto virtualTotal = 0;
  auto staticTotal = 0;
  auto staticWithSpanTotal = 0;
  auto dataOrientedTotal = 0;
  for (int i = 0; i < numberOfRepetitions; ++i) {
    auto start = std::chrono::steady_clock::now();
    srand(start.time_since_epoch().count());
    std::vector<std::unique_ptr<OO::Virtual::Model>> virtualModels;
    std::vector<OO::Static::Model> staticModels;
    OO::StaticWithSpan::Input staticWithSpanInput;
    DataOriented::Input dataOrientedInput;
    Tedious::makeModels(virtualModels, staticModels, staticWithSpanInput,
                        dataOrientedInput, numberOfModels,
                        numberOfAnimationsPerModel);

    Tedious::verifyInitialModels(virtualModels, staticModels,
                                 staticWithSpanInput.models,
                                 dataOrientedInput.inputValues);

    start = std::chrono::steady_clock::now();
    auto interpolatedVirtualModels =
        OO::Virtual::interpolateModels(virtualModels, 2);
    auto finish = std::chrono::steady_clock::now();
    virtualTotal += (finish - start).count();

    start = std::chrono::steady_clock::now();
    auto interpolatedStaticModels =
        OO::Static::interpolateModels(staticModels, 2);
    finish = std::chrono::steady_clock::now();
    staticTotal += (finish - start).count();

    start = std::chrono::steady_clock::now();
    auto interpolatedStaticWithSpanModels =
        OO::StaticWithSpan::interpolateModels(staticWithSpanInput.models, 2);
    finish = std::chrono::steady_clock::now();
    staticWithSpanTotal += (finish - start).count();

    start = std::chrono::steady_clock::now();
    DataOriented::interpolateModels(dataOrientedInput.inputValues,
                                    dataOrientedInput.interpolationResults, 2);
    finish = std::chrono::steady_clock::now();
    dataOrientedTotal += (finish - start).count();

    Tedious::verifyModels(interpolatedVirtualModels, interpolatedStaticModels,
                          interpolatedStaticWithSpanModels,
                          dataOrientedInput.models);
  }

  printf("Virtual: took time: %d\n", virtualTotal);
  printf("Static: took time: %d\n", staticTotal);
  printf("Static with span: took time: %d\n", staticWithSpanTotal);
  printf("Data oriented: took time: %d\n", dataOrientedTotal);
}

}  // namespace

int main(int argc, char *argv[]) {
  if (argc < 4) {
    printf(
        "Expecting number of models, number of animations per model, and "
        "number of repeat experiments.\n");
    return 1;
  }
  test(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  return 0;
}
