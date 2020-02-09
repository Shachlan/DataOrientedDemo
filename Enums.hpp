#pragma once

enum class Property { X, Y, Red, Green, Blue, Scale, Opacity };
enum class UpdateOperator { Multiply, Add, Replace };

constexpr float composeValue(float source, UpdateOperator op, float value) {
  switch (op) {
    case UpdateOperator::Multiply:
      return source * value;
    case UpdateOperator::Add:
      return source + value;
    case UpdateOperator::Replace:
      return value;
  }
}
