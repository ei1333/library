template< typename T, typename E = T >
struct SkewHeap {
  using G = function< T(T, E) >;
  using H = function< E(E, E) >;
 
  struct Node {
    T key;
    E lazy;
    Node *l, *r;
  };
 
  const bool rev;
  const G g;
  const H h;
 
  SkewHeap(bool rev = false) : g([](const T &a, const E &b) { return a + b; }),
                               h([](const E &a, const E &b) { return a + b; }), rev(rev) {}
 
  SkewHeap(const G &g, const H &h, bool rev = false) : g(g), h(h), rev(rev) {}
 
  Node *propagate(Node *t) {
    if(t->lazy != 0) {
      if(t->l) t->l->lazy = h(t->l->lazy, t->lazy);
      if(t->r) t->r->lazy = h(t->r->lazy, t->lazy);
      t->key = g(t->key, t->lazy);
      t->lazy = 0;
    }
    return t;
  }
 
  Node *merge(Node *x, Node *y) {
    if(!x || !y) return x ? x : y;
    propagate(x), propagate(y);
    if((x->key > y->key) ^ rev) swap(x, y);
    x->r = merge(y, x->r);
    swap(x->l, x->r);
    return x;
  }
 
  void push(Node *&root, const T &key) {
    root = merge(root, new Node({key, 0, nullptr, nullptr}));
  }
 
  T top(Node *root) {
    return propagate(root)->key;
  }
 
  T pop(Node *&root) {
    T top = propagate(root)->key;
    auto *temp = root;
    root = merge(root->l, root->r);
    delete temp;
    return top;
  }
 
  bool empty(Node *root) const {
    return !root;
  }
 
  void add(Node *root, const E &lazy) {
    if(root) {
      root->lazy = h(root->lazy, lazy);
      propagate(root);
    }
  }
 
  Node *makeheap() {
    return nullptr;
  }
};
