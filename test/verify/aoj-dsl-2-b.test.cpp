// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B

#include "../../template/template.hpp"

#include "../../structure/others/binary-indexed-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  BinaryIndexedTree< int > bit(N);
  while(Q--) {
    int T, X, Y;
    cin >> T >> X >> Y;
    if(T == 0) bit.apply(X - 1, Y);
    else cout << bit.prod(X - 1, Y) << "\n";
  }
}
