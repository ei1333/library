#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include "../../template/template.cpp"

#include "../../structure/others/link-cut-tree-subtree.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;

  struct Node {
    int64 sum;

    Node() : sum(0) {}

    void toggle() {}

    void merge(int64 cost, const Node &parent, const Node &child) {
      sum = cost + parent.sum + child.sum;
    }

    void add(const Node &chsum) {}

    void erase(const Node &chsum) {}
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
      int U, V;
      cin >> U >> V;
      lct.evert(vs[U]);
      cout << lct.query(vs[V]).sum << "\n";
    }
  }
}

