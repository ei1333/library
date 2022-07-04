/**
 * @brief Lazy-Weight-Balanced-Tree(遅延伝搬重み平衡木)
 */
template< typename Monoid, typename OperatorMonoid, typename F, typename G, typename H >
struct LazyWeightBalancedTree {
public:
  struct Node {
    Node *l, *r;
    int cnt;
    Monoid key, sum;
    OperatorMonoid lazy;

    Node() {}

    Node(const Monoid &k, const OperatorMonoid &laz) : key(k), sum(k), l(nullptr), r(nullptr), cnt(1), lazy(laz) {}

    Node(Node *l, Node *r, const Monoid &k, const OperatorMonoid &laz) : key(k), l(l), r(r), lazy(laz) {}

    bool is_leaf() { return !l || !r; }
  };

private:
  Node *propagate(Node *t) {
    t = clone(t);
    if(t->lazy != OM0) {
      if(t->is_leaf()) {
        t->key = g(t->key, t->lazy);
      } else {
        if(t->l) {
          t->l = clone(t->l);
          t->l->lazy = h(t->l->lazy, t->lazy);
          t->l->sum = g(t->l->sum, t->lazy);
        }
        if(t->r) {
          t->r = clone(t->r);
          t->r->lazy = h(t->r->lazy, t->lazy);
          t->r->sum = g(t->r->sum, t->lazy);
        }
      }
      t->lazy = OM0;
    }
    return update(t);
  }

  Node *update(Node *t) {
    t->cnt = count(t->l) + count(t->r) + t->is_leaf();
    t->sum = f(f(sum(t->l), t->key), sum(t->r));
    return t;
  }

  inline Node *alloc(Node *l, Node *r) {
    auto t = &(*pool.alloc() = Node(l, r, M1, OM0));
    return update(t);
  }

  Node *submerge(Node *l, Node *r) {
    if(count(l) > count(r) * 4) {
      l = propagate(l);
      auto nl = propagate(l->l);
      auto nr = submerge(l->r, r);
      if(count(nl) * 4 >= count(nr)) {
        l->r = nr;
        return update(l);
      }
      l->r = nr->l;
      nr->l = l;
      update(l);
      return update(nr);
    }
    if(count(l) * 4 < count(r)) {
      r = propagate(r);
      auto nl = submerge(l, r->l);
      auto nr = propagate(r->r);
      if(count(nl) <= count(nr) * 4) {
        r->l = nl;
        return update(r);
      }
      r->l = nl->r;
      nl->r = r;
      update(r);
      return update(nl);
    }
    return alloc(l, r);
  }

  Node *build(int l, int r, const vector< Monoid > &v) {
    if(l + 1 >= r) return alloc(v[l]);
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }

  void dump(Node *r, typename vector< Monoid >::iterator &it, OperatorMonoid lazy) {
    if(r->lazy != OM0) lazy = h(lazy, r->lazy);
    if(r->is_leaf()) {
      *it++ = g(r->key, lazy);
      return;
    }
    dump(r->l, it, lazy);
    dump(r->r, it, lazy);
  }

  virtual Node *clone(Node *t) {
    return t;
  }

  Node *merge(Node *l) {
    return l;
  }


public:
  VectorPool< Node > pool;
  const F f;
  const G g;
  const H h;
  const Monoid M1;
  const OperatorMonoid OM0;

  LazyWeightBalancedTree(int sz, const F &f, const G &g, const H &h, const Monoid &M1, const OperatorMonoid &OM0)
      : pool(sz), M1(M1), f(f), g(g), h(h), OM0(OM0) {
    pool.clear();
  }

  inline Node *alloc(const Monoid &key) {
    return &(*pool.alloc() = Node(key, OM0));
  }

  static inline int count(const Node *t) { return t ? t->cnt : 0; }

  inline const Monoid &sum(const Node *t) { return t ? t->sum : M1; }

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

  tuple< Node *, Node *, Node * > split3(Node *t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    return make_tuple(x.first, y.first, y.second);
  }

  template< typename ... Args >
  Node *merge(Node *l, Args ...rest) {
    Node *r = merge(rest...);
    if(!l || !r) return l ? l : r;
    return submerge(l, r);
  }

  Node *build(const vector< Monoid > &v) {
    return build(0, (int) v.size(), v);
  }

  vector< Monoid > dump(Node *r) {
    vector< Monoid > v((size_t) count(r));
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
    return ret;
  }

  void insert(Node *&t, int k, const Monoid &v) {
    auto x = split(t, k);
    t = merge(merge(x.first, alloc(v)), x.second);
  }

  Monoid erase(Node *&t, int k) {
    auto x = split(t, k);
    auto y = split(x.second, 1);
    auto v = y.first->c;
    pool.free(y.first);
    t = merge(x.first, y.second);
    return v;
  }

  Monoid query(Node *&t, int a, int b) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    Monoid ret = sum(y.first);
    t = merge(x.first, y.first, y.second);
    return ret;
  }

  void set_propagate(Node *&t, int a, int b, const OperatorMonoid &pp) {
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    y.first->lazy = h(y.first->lazy, pp);
    t = merge(x.first, propagate(y.first), y.second);
  }

  void set_element(Node *&t, int k, const Monoid &x) {
    t = propagate(t);
    if(t->is_leaf()) {
      t->key = t->sum = x;
      return;
    }
    if(k < count(t->l)) set_element(t->l, k, x);
    else set_element(t->r, k - count(t->l), x);
    t = update(t);
  }

  void push_front(Node *&t, const Monoid &v) {
    t = merge(alloc(v), t);
  }

  void push_back(Node *&t, const Monoid &v) {
    t = merge(t, alloc(v));
  }

  Monoid pop_front(Node *&t) {
    auto ret = split(t, 1);
    t = ret.second;
    return ret.first->key;
  }

  Monoid pop_back(Node *&t) {
    auto ret = split(t, count(t) - 1);
    t = ret.first;
    return ret.second->key;
  }
};
