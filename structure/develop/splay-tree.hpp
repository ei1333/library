template< typename key_t, size_t V >
struct SplayTree {

  const key_t e;

  SplayTree() : pool(), e(key_t()) {}

  struct Node {
    Node *l, *r, *p;
    key_t sum;

    Node() = default;

    explicit Node(const key_t &k) : sum(k), l(nullptr), r(nullptr), p(nullptr) {}
  };

  ArrayPool< Node, V > pool;

private:
  void rotr(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(Node *t) {
    auto *x = t->p, *y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void update(Node *t) {
    t->sum.set_sum();
    if(t->l) t->sum.update(t->l->sum);
    if(t->r) t->sum.update(t->r->sum);
  }

  Node *get_right(Node *t) const {
    while(t->r) t = t->r;
    return t;
  }

  inline Node *alloc(const key_t &v) {
    auto p = &(*pool.alloc() = Node(v));
    update(p);
    return p;
  }

  void splay(Node *t) {
    while(t->p) {
      auto *q = t->p;
      if(!q->p) {
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        auto *r = q->p;
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

public:
  inline const key_t &sum(Node *t) {
    return t ? t->sum : e;
  }

  Node *push_back(Node *t, const key_t &v) {
    if(!t) {
      t = alloc(v);
      return t;
    } else {
      Node *cur = get_right(t), *z = alloc(v);
      z->p = cur;
      cur->r = z;
      update(cur);
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
      update(t);
    }
    return t;
  }
};
