template< class T >
struct ArrayPool {
  vector< T > pool;
  vector< T * > stock;
  int ptr;

  ArrayPool(int sz) : pool(sz), stock(sz) {}

  inline T *alloc() { return stock[--ptr]; }

  inline void free(T *t) { stock[ptr++] = t; }

  void clear() {
    ptr = (int) pool.size();
    for(int i = 0; i < pool.size(); i++) stock[i] = &pool[i];
  }
};

template< class D, class L, D (*f)(D, D), D (*g)(D, L), L (*h)(L, L), L (*p)(L, int) >
struct RedBlackTree {
  enum COLOR {
    BLACK, RED
  };

  struct Node {
    Node *l, *r;
    COLOR color;
    int level, cnt;
    D key, sum;
    L lazy;

    Node() {}

    Node(const D &k, const L &laz) :
        key(k), sum(k), l(nullptr), r(nullptr), color(BLACK), level(0), cnt(1), lazy(laz) {}

    Node(Node *l, Node *r, const D &k, const L &laz) :
        key(k), color(RED), l(l), r(r), lazy(laz) {}
  };

  ArrayPool< Node > pool;


  const D M1;
  const L OM0;

  RedBlackTree(int sz, const D &M1, const L &OM0) :
      pool(sz), M1(M1), OM0(OM0) { pool.clear(); }


  inline Node *alloc(const D &key) {
    return &(*pool.alloc() = Node(key, OM0));
  }

  inline Node *alloc(Node *l, Node *r) {
    auto t = &(*pool.alloc() = Node(l, r, M1, OM0));
    return update(t);
  }

  virtual Node *clone(Node *t) { return t; }

  inline int count(const Node *t) { return t ? t->cnt : 0; }

  inline D sum(const Node *t) { return t ? t->sum : M1; }

  Node *update(Node *t) {
    t->cnt = count(t->l) + count(t->r) + (!t->l || !t->r);
    t->level = t->l ? t->l->level + (t->l->color == BLACK) : 0;
    t->sum = f(f(sum(t->l), t->key), sum(t->r));
    return t;
  }

  Node *propagate(Node *t) {
    t = clone(t);
    if(t->lazy != OM0) {
      if(!t->l) {
        t->key = g(t->key, p(t->lazy, 1));
      } else {
        if(t->l) {
          t->l = clone(t->l);
          t->l->lazy = h(t->l->lazy, t->lazy);
          t->l->sum = g(t->l->sum, p(t->lazy, count(t->l)));
        }
        if(t->r) {
          t->r = clone(t->r);
          t->r->lazy = h(t->r->lazy, t->lazy);
          t->r->sum = g(t->r->sum, p(t->lazy, count(t->r)));
        }
      }
      t->lazy = OM0;
    }
    return update(t);
  }

  Node *rotate(Node *t, bool b) {
    t = propagate(t);
    Node *s;
    if(b) {
      s = propagate(t->l);
      t->l = s->r;
      s->r = t;
    } else {
      s = propagate(t->r);
      t->r = s->l;
      s->l = t;
    }
    update(t);
    return update(s);
  }

  Node *submerge(Node *l, Node *r) {
    if(l->level < r->level) {
      r = propagate(r);
      Node *c = (r->l = submerge(l, r->l));
      if(r->color == BLACK && c->color == RED && c->l && c->l->color == RED) {
        r->color = RED;
        c->color = BLACK;
        if(r->r->color == BLACK) return rotate(r, true);
        r->r->color = BLACK;
      }
      return update(r);
    }
    if(l->level > r->level) {
      l = propagate(l);
      Node *c = (l->r = submerge(l->r, r));
      if(l->color == BLACK && c->color == RED && c->r && c->r->color == RED) {
        l->color = RED;
        c->color = BLACK;
        if(l->l->color == BLACK) return rotate(l, false);
        l->l->color = BLACK;
      }
      return update(l);
    }
    return alloc(l, r);
  }

  Node *merge(Node *l, Node *r) {
    if(!l || !r) return l ? l : r;
    Node *c = submerge(l, r);
    c->color = BLACK;
    return c;
  }

  pair< Node *, Node * > split(Node *t, int k) {
    if(!t) return {nullptr, nullptr};
    t = propagate(t);
    if(k == 0) return {nullptr, t};
    if(k >= count(t)) return {t, nullptr};
    Node *l = t->l, *r = t->r;
    pool.free(t);
    if(k < count(l)) {
      auto pp = split(l, k);
      return {pp.first, merge(pp.second, r)};
    }
    if(k > count(l)) {
      auto pp = split(r, k - count(l));
      return {merge(l, pp.first), pp.second};
    }
    return {l, r};
  }

  Node *build(int l, int r, const vector< D > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  Node *build(const vector< D > &v) {
    //pool.clear();
    return build(0, (int) v.size(), v);
  }

  void dump(Node *r, typename vector< D >::iterator &it, L lazy) {
    if(r->lazy != OM0) lazy = h(lazy, r->lazy);
    if(!r->l || !r->r) {
      *it++ = g(r->key, lazy);
      return;
    }
    dump(r->l, it, lazy);
    dump(r->r, it, lazy);
  }

  vector< D > dump(Node *r) {
    vector< D > v((size_t) count(r));
    auto it = begin(v);
    dump(r, it, OM0);
    return v;
  }

  string to_string(Node *r) {
    auto s = dump(r);
    string ret;
    for(int i = 0; i < s.size(); i++) {
      ret += std::to_string(s[i]);
      ret += ", ";
    }
    return (ret);
  }

  void insert(Node *&t, int k, const D &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  D erase(Node *&t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    auto v = y.first->key;
    pool.free(y.first);
    t = merge(x.first, y.second);
    return v;
  }

  D query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  void set_propagate(Node *&t, int a, int b, const L &pp) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    y.first->lazy = h(y.first->lazy, pp);
    t = merge(x.first, merge(propagate(y.first), y.second));
  }

  void set_element(Node *&t, int k, const D &x) {
    if(!t->l) {
      t->key = t->sum = x;
      return;
    }
    t = propagate(t);
    if(k < count(t->l)) set_element(t->l, k, x);
    else set_element(t->r, k - count(t->l), x);
    t = update(t);
  }

  int size(Node *t) {
    return count(t);
  }

  bool empty(Node *t) {
    return !t;
  }

  Node *makeset() {
    return (nullptr);
  }
};
