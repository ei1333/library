// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2270

#include "../../template/template.hpp"

#include "../../other/mo-tree.hpp"

#include "../../structure/others/binary-indexed-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto &a: A) cin >> a;
  auto vs = A;
  sort(begin(vs), end(vs));
  vs.erase(unique(begin(vs), end(vs)), end(vs));
  for(auto &a: A) a = lower_bound(begin(vs), end(vs), a) - begin(vs);
  MoTree<> g(N);
  g.read(N - 1);
  vector< int > K(Q);
  for(int i = 0; i < Q; i++) {
    int a, b;
    cin >> a >> b >> K[i];
    --a, --b;
    g.add(a, b);
  }
  vector< int64 > ans(Q);
  BinaryIndexedTree< int > bit(N);
  int64 sum = 0;
  auto add = [&](int i) {
    bit.apply(A[i], 1);
  };
  auto erase = [&](int i) {
    bit.apply(A[i], -1);
  };
  auto out = [&](int q) {
    ans[q] = vs[bit.lower_bound(K[q])];
  };
  g.build(add, erase, out);
  for(auto &p: ans) cout << p << "\n";
}
