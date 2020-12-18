/**
 * @brief Skew-Heap
 */
template< typename T, bool isMin = true >
struct SkewHeap {
  struct Node {
    T key, lazy;
    Node *l, *r;
    int idx;

    explicit Node(const T &key, int idx) : key(key), idx(idx), lazy(0), l(nullptr), r(nullptr) {}
  };

  SkewHeap() = default;

  Node *alloc(const T &key, int idx = -1) {
    return new Node(key, idx);
  }

  Node *propagate(Node *t) {
    if(t && t->lazy != 0) {
      if(t->l) t->l->lazy += t->lazy;
      if(t->r) t->r->lazy += t->lazy;
      t->key += t->lazy;
      t->lazy = 0;
    }
    return t;
  }

  Node *meld(Node *x, Node *y) {
    propagate(x), propagate(y);
    if(!x || !y) return x ? x : y;
    if((x->key < y->key) ^ isMin) swap(x, y);
    x->r = meld(y, x->r);
    swap(x->l, x->r);
    return x;
  }

  Node *push(Node *t, const T &key, int idx = -1) {
    return meld(t, alloc(key, idx));
  }

  Node *pop(Node *t) {
    assert(t != nullptr);
    return meld(t->l, t->r);
  }

  Node *add(Node *t, const T &lazy) {
    if(t) {
      t->lazy += lazy;
      propagate(t);
    }
    return t;
  }

  Node *make_root() {
    return nullptr;
  }
};
