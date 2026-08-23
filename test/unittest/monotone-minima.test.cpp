// competitive-verifier: STANDALONE

#include "../../dp/monotone-minima.hpp"

#include <cassert>
#include <random>
#include <vector>

int main() {
  const std::vector<std::vector<int>> matrix = {
      {0, 1, 4, 9, 16},
      {4, 1, 0, 1, 4},
      {16, 9, 4, 1, 0},
  };
  auto argmin =
      monotone_minima(3, 5, [&](int row, int old_column, int new_column) {
        return matrix[row][new_column] < matrix[row][old_column];
      });
  assert((argmin == std::vector<int>{0, 2, 4}));

  auto empty_rows = monotone_minima(0, 5, [](int, int, int) { return false; });
  assert(empty_rows.empty());
  auto empty_columns =
      monotone_minima(3, 0, [](int, int, int) { return false; });
  assert((empty_columns == std::vector<int>{-1, -1, -1}));

  std::mt19937 random(123456789);
  for (int height = 1; height <= 30; ++height) {
    for (int width = 1; width <= 30; ++width) {
      std::vector<int> center(height);
      for (int row = 1; row < height; ++row) {
        center[row] = center[row - 1] + random() % 3;
      }
      for (int& column : center) column %= width;
      for (int row = 1; row < height; ++row) {
        if (center[row] < center[row - 1]) center[row] = center[row - 1];
      }
      auto result = monotone_minima(
          height, width, [&](int row, int old_column, int new_column) {
            int old_distance = old_column - center[row];
            int new_distance = new_column - center[row];
            return new_distance * new_distance < old_distance * old_distance;
          });
      assert(result == center);
    }
  }
}
