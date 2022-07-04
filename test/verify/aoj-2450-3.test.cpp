#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"

#include "../../template/template.hpp"

#include "../../structure/develop/splay-tree-base.hpp"
#include "../../structure/develop/reversible-splay-tree.hpp"
#include "../../structure/develop/lazy-reversible-splay-tree.hpp"
#include "../../structure/develop/link-cut-tree.hpp"

int main() {
  int N, Q, S[200000];
  cin >> N >> Q;

  struct Node {
    int64 ans, all, left, right, length;

    Node() : ans(-infll), all(0), left(-infll), right(-infll), length(0) {}

    Node(int64 val, int64 len) : length(len) {
      all = val * len;
      ans = left = right = (val > 0 ? all : val);
    }

    Node operator+(const Node &s) const {
      Node ret;
      ret.length = length + s.length;
      ret.ans = max({ans, s.ans, right + s.left});
      ret.all = all + s.all;
      ret.left = max(left, all + s.left);
      ret.right = max(s.right, right + s.all);
      return ret;
    }
  };
  auto F = [](const Node &a, const Node &b) { return a + b; };
  auto G = [](const Node &a, int64 x) { return Node(x, a.length); };
  auto H = [](int64, int64 y) { return y; };
  auto T = [](Node a) {
    swap(a.left, a.right);
    return a;
  };


  using LCT = LinkCutTree< LRST< Node, int64 > >;
  LCT lct(F, G, H, T, Node(), infll);
  vector< LCT::Node * > vs(N);

  for(int i = 0; i < N; i++) {
    cin >> S[i];
    vs[i] = lct.alloc(Node(S[i], 1));
  }
  for(int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    lct.evert(vs[v]);
    lct.link(vs[v], vs[u]);
  }
  while(Q--) {
    int X, A, B, C;
    cin >> X >> A >> B >> C;
    --A, --B;
    if(X == 1) {
      lct.evert(vs[A]);
      lct.expose(vs[B]);
      lct.set_propagate(vs[B], C);
    } else {
      lct.evert(vs[A]);
      lct.expose(vs[B]);
      cout << vs[B]->sum.ans << "\n";
    }
  }
}
