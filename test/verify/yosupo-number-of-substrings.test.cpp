// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/number_of_substrings

#include "../../template/template.hpp"

#include "../../string/lcp-array.hpp"

int main() {
  string S;
  cin >> S;
  int N = (int) S.size();
  SuffixArray sa(S);
  auto lcp = lcp_array(sa);
  cout << 1LL * N * (N + 1) / 2 - accumulate(begin(lcp), end(lcp), 0LL) << "\n";
}
