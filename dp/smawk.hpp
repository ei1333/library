#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

template <typename F>
std::vector<int> smawk(int H, int W, F comp) {
  std::vector<int> ret(H, -1);
  if (H == 0 || W == 0) return ret;

  auto dfs = [&](auto&& self, const std::vector<int>& rows,
                 const std::vector<int>& cols) -> void {
    if (rows.empty()) return;
    std::vector<int> reduced;
    reduced.reserve(std::min(rows.size(), cols.size()));
    for (int c : cols) {
      while (!reduced.empty()) {
        int r = rows[reduced.size() - 1];
        int old_c = reduced.back();
        if (comp(r, old_c, c)) {
          reduced.pop_back();
        } else {
          break;
        }
      }
      if (reduced.size() < rows.size()) reduced.emplace_back(c);
    }

    std::vector<int> odd_rows;
    odd_rows.reserve(rows.size() / 2);
    for (int i = 1; i < static_cast<int>(rows.size()); i += 2) {
      odd_rows.emplace_back(rows[i]);
    }
    self(self, odd_rows, reduced);

    int left = 0;
    for (int i = 0; i < static_cast<int>(rows.size()); i += 2) {
      int right = static_cast<int>(reduced.size()) - 1;
      if (i + 1 < static_cast<int>(rows.size())) {
        right = left;
        while (reduced[right] != ret[rows[i + 1]]) ++right;
      }
      int best = left;
      for (int p = left + 1; p <= right; ++p) {
        if (comp(rows[i], reduced[best], reduced[p])) best = p;
      }
      ret[rows[i]] = reduced[best];
      left = right;
    }
  };

  std::vector<int> rows(H), cols(W);
  std::iota(rows.begin(), rows.end(), 0);
  std::iota(cols.begin(), cols.end(), 0);
  dfs(dfs, rows, cols);
  return ret;
}
