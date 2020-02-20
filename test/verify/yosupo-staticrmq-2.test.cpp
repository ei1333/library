#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../structure/others/disjoint-sparse-table.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  auto f = [](int a, int b) { return min(a, b); };
  DisjointSparseTable< int > st(A, f);
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l, r) << "\n";
  }
}
