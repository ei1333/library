#pragma once

#include <vector>

template <typename Select>
std::vector<int> monotone_minima_select(int H, int W, Select select) {
  std::vector<int> ret(H, -1);
  if (H == 0 || W == 0) return ret;
  auto dfs = [&](auto&& self, int top, int bottom, int left,
                 int right) -> void {
    if (top > bottom) return;
    int line = (top + bottom) / 2;
    int best = select(line, left, right);
    ret[line] = best;
    self(self, top, line - 1, left, best);
    self(self, line + 1, bottom, best, right);
  };
  dfs(dfs, 0, H - 1, 0, W - 1);
  return ret;
}

template <typename F>
std::vector<int> monotone_minima(int H, int W, F comp) {
  return monotone_minima_select(H, W, [&](int row, int left, int right) {
    int best = left;
    for (int column = left + 1; column <= right; ++column) {
      if (comp(row, best, column)) best = column;
    }
    return best;
  });
}
