#include <chrono>
#include <cstdlib>

#include "TediousStuff.hpp"

namespace {

constexpr int kNumberOfRepetitions = 1;

void test() {
  double virtualTotal = 0;
  double staticTotal = 0;
  double staticWithSpanTotal = 0;
  double dataOrientedTotal = 0;
  for (int i = 0; i < kNumberOfRepetitions; ++i) {
    auto start = std::chrono::steady_clock::now();
    srand(start.time_since_epoch().count());
    std::vector<std::unique_ptr<OO::Virtual::Model>> virtualModels;
    std::vector<OO::Static::Model> staticModels;
    OO::StaticWithSpan::Input staticWithSpanInput;
    DataOriented::Input dataOrientedInput;
    Tedious::makeModels(virtualModels, staticModels, staticWithSpanInput,
                        dataOrientedInput);

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

  printf("Virtual: took time: %f\n", virtualTotal);
  printf("Static: took time: %f\n", staticTotal);
  printf("Static with span: took time: %f\n", staticWithSpanTotal);
  printf("Data oriented: took time: %f\n", dataOrientedTotal);
}

}  // namespace

int main(int argc, char *argv[]) { test(); }
