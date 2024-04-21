// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum

#include "../../template/template.hpp"

#include "../../structure/lct/link-cut-tree-subtree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;


  struct Node {
    int64 sum, psum, csum, lsum;

    Node() : sum(0), lsum(0), psum(0), csum(0) {}

    void toggle() {
      swap(psum, csum);
    }

    void merge(int64 cost, const Node &parent, const Node &child) {
      sum = cost + parent.sum + child.sum + lsum;
      psum = parent.psum + cost + lsum;
      csum = child.csum + cost + lsum;
    }

    void add(const Node &chsum) {
      lsum += chsum.sum;
    }

    void erase(const Node &chsum) {
      lsum -= chsum.sum;
    }
  } e;

  using LCT = LinkCutTreeSubtree< Node, int64 >;
  LCT lct(e);

  vector< int > A(N);
  cin >> A;

  vector< LCT::Node * > vs(N), es(N);
  for(int i = 0; i < N; i++) {
    vs[i] = lct.make_node(A[i]);
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    lct.evert(vs[b]);
    lct.link(vs[b], vs[a]);
  }

  while(Q--) {
    int T;
    cin >> T;
    if(T == 0) {
      int U, V, W, X;
      cin >> U >> V >> W >> X;
      lct.evert(vs[U]);
      lct.cut(vs[V]);
      lct.evert(vs[W]);
      lct.link(vs[W], vs[X]);
    } else if(T == 1) {
      int P, X;
      cin >> P >> X;
      lct.set_key(vs[P], vs[P]->key + X);
    } else {
      int V, P;
      cin >> V >> P;
      lct.evert(vs[P]);
      cout << lct.query(vs[V]).csum << "\n";
    }
  }
}

