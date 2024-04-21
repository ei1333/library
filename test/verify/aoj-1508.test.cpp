// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508

#include "../../template/template.hpp"

#include "../../structure/bbst/randomized-binary-search-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto &a : A) cin >> a;
  auto f = [](int a, int b) { return min(a, b); };
  RandomizedBinarySearchTree< int > rbst(N + Q, f, inf);
  auto V = rbst.build(A);
  while(Q--) {
    int X, Y, Z;
    cin >> X >> Y >> Z;
    if(X == 0) {
      auto S = rbst.split3(V, Y, Z + 1);
      auto val = rbst.pop_back(get< 1 >(S));
      rbst.push_front(get< 1 >(S), val);
      V = rbst.merge(get< 0 >(S), get< 1 >(S), get< 2 >(S));
    } else if(X == 1) {
      cout << rbst.query(V, Y, Z + 1) << "\n";
    } else {
      rbst.set_element(V, Y, Z);
    }
  }
}
