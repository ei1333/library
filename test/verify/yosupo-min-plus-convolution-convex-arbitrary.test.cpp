// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/min-plus-convolution-convex-arbitary.hpp"

int main() {
  int N, M;
  std::cin >> N >> M;
  std::vector<long long> A(N), B(M);
  for (long long& a : A) std::cin >> a;
  for (long long& b : B) std::cin >> b;
  auto C = min_plus_convolution_convex_arbitary(A, B);
  for (int i = 0; i < static_cast<int>(C.size()); ++i) {
    if (i) std::cout << ' ';
    std::cout << C[i];
  }
  std::cout << '\n';
}
