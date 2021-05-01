#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "../../template/template.cpp"

#include "../../structure/others/binary-indexed-tree.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  BinaryIndexedTree< int > bit(N);
  while(Q--) {
    int T, X, Y;
    cin >> T >> X >> Y;
    if(T == 0) bit.add(X - 1, Y);
    else cout << bit.fold(X - 1, Y) << "\n";
  }
}
