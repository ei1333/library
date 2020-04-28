#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../other/vector-pool.cpp"

#include "../../structure/bbst/red-black-tree.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  auto f = [](int a, int b) { return min(a, b); };
  RedBlackTree< int, decltype(f) > rbt(2 * N, f, inf);
  auto root = rbt.build(A);
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << rbt.query(root, l, r) << "\n";
  }
}

