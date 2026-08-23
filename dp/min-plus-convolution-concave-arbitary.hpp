#pragma once

#include <algorithm>
#include <limits>
#include <vector>

#include "smawk.hpp"

template <typename T>
std::vector<T> min_plus_convolution_concave_arbitary(const std::vector<T>& a,
                                                     const std::vector<T>& b) {
  if (a.empty() || b.empty()) return {};
  int N = static_cast<int>(a.size());
  int M = static_cast<int>(b.size());
  int H = N + M - 1;

  std::vector<int> column_min(H, 0), column_max(H, M - 1);
  for (int row = N; row < H; ++row) column_min[row] = row - N + 1;
  for (int row = 0; row <= H - N; ++row) column_max[row] = row;

  std::vector<int> row_min(M), row_max(M);
  for (int column = 0; column < M; ++column) {
    row_min[column] = column;
    row_max[column] = N - 1 + column;
  }

  std::vector<T> result(H, std::numeric_limits<T>::max());
  auto divide = [&](auto&& self, int row_left, int row_right, int column_left,
                    int column_right) -> void {
    if (column_max[row_left] >= column_right &&
        column_left >= column_min[row_right]) {
      auto value = [&](int row, int column) {
        int j = column_right - column;
        return b[j] + a[row_left + row - j];
      };
      auto argmin =
          smawk(row_right - row_left + 1, column_right - column_left + 1,
                [&](int row, int old_column, int new_column) {
                  return value(row, new_column) < value(row, old_column);
                });
      for (int row = row_left; row <= row_right; ++row) {
        result[row] = std::min(result[row],
                               value(row - row_left, argmin[row - row_left]));
      }
      return;
    }

    if (row_right - row_left > column_right - column_left) {
      int row_middle = (row_left + row_right) / 2;
      int next_column_right = std::min(column_max[row_middle], column_right);
      if (column_left <= next_column_right) {
        self(self, row_left, row_middle, column_left, next_column_right);
      }
      int next_column_left = std::max(column_min[row_middle], column_left);
      if (next_column_left <= column_right) {
        self(self, row_middle + 1, row_right, next_column_left, column_right);
      }
    } else {
      int column_middle = (column_left + column_right) / 2;
      int next_row_right = std::min(row_max[column_middle], row_right);
      if (row_left <= next_row_right) {
        self(self, row_left, next_row_right, column_left, column_middle);
      }
      int next_row_left = std::max(row_min[column_middle], row_left);
      if (next_row_left <= row_right) {
        self(self, next_row_left, row_right, column_middle + 1, column_right);
      }
    }
  };
  divide(divide, 0, H - 1, 0, M - 1);
  return result;
}
