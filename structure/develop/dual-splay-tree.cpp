template< typename E, typename OpEE, size_t V >
struct DualSplayTree {
  const E e0;
  const OpEE h;

  DualSplayTree(const OpEE &h, const E &e0) : pool(), e0(e0), h(h) {}

  struct Node {
    Node *l, *r, *p;
    E val, lazy;

    Node() = default;

    Node(const E &val, const E &lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr), p(nullptr) {}
  };

  ArrayPool< Node, V > pool;

  void push(Node *t) {
    if(t->lazy != e0) {
      if(t->l) propagate(t->l, t->lazy);
      if(t->r) propagate(t->r, t->lazy);
      t->lazy = e0;
    }
  }

  void propagate(Node *t, const E &x) {
    t->lazy = h(t->lazy, x);
    t->val = h(t->val, x);
  }

  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  Node *get_left(Node *t) const {
    while(t->l) t = t->l;
    return t;
  }

  Node *get_right(Node *t) const {
    while(t->r) t = t->r;
    return t;
  }

  inline Node *alloc(const E &val) {
    return &(*pool.alloc() = Node(val, e0));
  }

  void splay(Node *t) {
    push(t);
    while(t->p) {
      auto *q = t->p;
      if(!q->p) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
        push(r), push(q), push(t);
        if(r->l == q) {
          if(q->l == t) rotr(q), rotr(t);
          else rotl(t), rotr(t);
        } else {
          if(q->r == t) rotl(q), rotl(t);
          else rotr(t), rotl(t);
        }
      }
    }
  }

  Node *push_back(Node *t, const E &val) {
    if(!t) {
      t = alloc(val);
      return t;
    } else {
      Node *cur = get_right(t), *z = alloc(val);
      splay(cur);
      z->p = cur;
      cur->r = z;
      splay(z);
      return z;
    }
  }

  Node *erase(Node *t) {
    splay(t);
    Node *x = t->l, *y = t->r;
    pool.free(t);
    if(!x) {
      t = y;
      if(t) t->p = nullptr;
    } else if(!y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
    }
    return t;
  }

  void set_propagate(Node *t, const E &x) {
    if(t) {
      splay(t);
      propagate(t, x);
      push(t);
    }
  }
};

template< size_t V, typename E, typename OpEE >
DualSplayTree< E, OpEE, V > get_dual_splay_tree(const E &e0, const OpEE &h) {
  return DualSplayTree< E, OpEE, V >(h, e0);
}
