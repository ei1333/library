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
  auto selected =
      monotone_minima_select(3, 5, [&](int row, int left, int right) {
        int best = left;
        for (int column = left + 1; column < right; ++column) {
          if (matrix[row][column] < matrix[row][best]) best = column;
        }
        return best;
      });
  assert(selected == argmin);

  auto empty_rows = monotone_minima(0, 5, [](int, int, int) { return false; });
  assert(empty_rows.empty());
  auto empty_columns =
      monotone_minima(3, 0, [](int, int, int) { return false; });
  assert((empty_columns == std::vector<int>{-1, -1, -1}));
  int select_calls = 0;
  auto empty_select = monotone_minima_select(
      3, 0, [&](int, int, int) { return ++select_calls; });
  assert((empty_select == std::vector<int>{-1, -1, -1}));
  assert(select_calls == 0);

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
