#pragma once

#include <vector>

#include "smawk.hpp"

template <typename T>
std::vector<T> min_plus_convolution_convex_arbitary(const std::vector<T>& a,
                                                    const std::vector<T>& b) {
  if (a.empty() || b.empty()) return {};
  int H = static_cast<int>(a.size());
  int W = static_cast<int>(b.size());
  const auto c = smawk(H + W - 1, W, [&](int i, int j, int k) {
    if (i < k) return false;
    if (i - j >= H) return true;
    return b[k] + a[i - k] < b[j] + a[i - j];
  });
  std::vector<T> ret;
  ret.reserve(H + W - 1);
  for (int i = 0; i < H + W - 1; ++i) {
    ret.emplace_back(b[c[i]] + a[i - c[i]]);
  }
  return ret;
}
