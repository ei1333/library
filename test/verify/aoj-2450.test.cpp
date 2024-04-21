// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450

#include "../../template/template.hpp"

#include "../../structure/segment-tree/lazy-segment-tree.hpp"

#include "../../graph/tree/heavy-light-decomposition.hpp"

int main() {
  int N, Q, S[200000];
  cin >> N >> Q;
  for(int i = 0; i < N; i++) {
    cin >> S[i];
  }
  HeavyLightDecomposition< int64 > tree(N);
  tree.read(N - 1);
  tree.build();

  struct Node {
    int64 ans, all, left, right, length;

    Node() : ans(-infll), all(0), left(-infll), right(-infll), length(0) {}

    Node(int64 val, int64 len) {
      length = len;
      all = val * length;
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
  auto H = [](int64 x, int64 y) { return y; };
  auto seg = get_lazy_segment_tree(N, F, G, H, Node(), infll);
  for(int i = 0; i < N; i++) seg.set(i, Node(S[tree.rev[i]], 1));

  auto QF = [&](int a, int b) { return seg.prod(a, b); };
  auto QG = [](const Node &a, const Node &b) { return a + b; };
  auto QS = [](Node l, const Node &r) {
    swap(l.left, l.right);
    return l + r;
  };

  while(Q--) {
    int T, A, B, C;
    cin >> T >> A >> B >> C;
    --A, --B;
    if(T == 1) {
      tree.add(A, B, [&](int a, int b) { seg.apply(a, b, C); });
    } else {
      cout << tree.query(A, B, Node(), QF, QG, QS).ans << "\n";
    }
  }
}

