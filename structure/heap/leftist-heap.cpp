/**
 * @brief Leftist-Heap
 */
template< typename T, bool isMin = true >
struct LeftistHeap {
  struct Node {
    Node *l, *r;
    int s;
    T key;

    explicit Node(const T &key) : key(key), s(1), l(nullptr), r(nullptr) {}
  };

  LeftistHeap() = default;

  virtual Node *clone(Node *t) {
    return t;
  }

  Node *alloc(const T &key) {
    return new Node(key);
  }

  Node *meld(Node *a, Node *b) {
    if(!a || !b) return a ? a : b;
    if((a->key < b->key) ^ isMin) swap(a, b);
    a = clone(a);
    a->r = meld(a->r, b);
    if(!a->l || a->l->s < a->r->s) swap(a->l, a->r);
    a->s = (a->r ? a->r->s : 0) + 1;
    return a;
  }

  Node *push(Node *t, const T &key) {
    return meld(t, alloc(key));
  }

  Node *pop(Node *t) {
    assert(t != nullptr);
    auto ret = meld(t->l, t->r);
    delete t;
    return ret;
  }

  Node *make_root() {
    return nullptr;
  }
};
