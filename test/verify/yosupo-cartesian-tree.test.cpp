// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/cartesian_tree

#include "../../template/template.hpp"

#include "../../graph/others/cartesian-tree.hpp"

int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  for(auto &a : A) cin >> a;
  auto p = cartesian_tree(A);
  for(int i = 0; i < N; i++) {
    if(p[i] >= 0) cout << p[i] << " ";
    else cout << i << " ";
  }
  cout << "\n";
}
