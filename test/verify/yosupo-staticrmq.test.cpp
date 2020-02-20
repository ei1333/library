#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../template/template.cpp"

#include "../../structure/others/sparse-table.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  SparseTable< int > st(A);
  while(Q--) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l, r) << "\n";
  }
}
