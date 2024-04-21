// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508

#include "../../template/template.hpp"

#include "../../other/vector-pool.hpp"
#include "../../structure/bbst/weight-balanced-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto &a : A) cin >> a;
  auto f = [](int a, int b) { return min(a, b); };
  WeightBalancedTree< int, decltype(f) > rbt((N + Q) * 2, f, inf);
  auto V = rbt.build(A);
  while(Q--) {
    int X, Y, Z;
    cin >> X >> Y >> Z;
    if(X == 0) {
      auto S = rbt.split3(V, Y, Z + 1);
      auto val = rbt.pop_back(get< 1 >(S));
      rbt.push_front(get< 1 >(S), val);
      V = rbt.merge(get< 0 >(S), get< 1 >(S), get< 2 >(S));
    } else if(X == 1) {
      cout << rbt.query(V, Y, Z + 1) << "\n";
    } else {
      rbt.set_element(V, Y, Z);
    }
  }
}
