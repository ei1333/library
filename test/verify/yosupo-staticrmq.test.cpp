#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../structure/others/sparse-table.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  auto st = get_sparse_table(A, [](int a, int b) { return min(a, b); });
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.fold(l, r) << "\n";
  }
}
