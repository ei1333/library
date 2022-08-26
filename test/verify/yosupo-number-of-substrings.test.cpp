#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../string/lcp-array.hpp"
#include "../../template/template.hpp"

int main() {
  string S;
  cin >> S;
  int N = (int)S.size();
  SuffixArray sa(S);
  auto lcp = lcp_array(sa);
  cout << 1LL * N * (N + 1) / 2 -
          accumulate(begin(lcp), end(lcp), 0LL)
       << "\n";
}
