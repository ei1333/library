/**
 * @brief Reversible-Splay-Tree(反転可能Splay木)
 */
template< typename Tp >
struct ReversibleSplayTreeNode {
  using T = Tp;
  ReversibleSplayTreeNode *l, *r, *p;
  T key, sum;
  bool rev;
  size_t sz;

  ReversibleSplayTreeNode() : ReversibleSplayTreeNode(Tp()) {}

  ReversibleSplayTreeNode(const T &key) :
      key(key), sum(key), rev(false), l(nullptr), r(nullptr), p(nullptr), sz(1) {}
};

template< typename Np >
struct ReversibleSplayTree : SplayTreeBase< Np > {
public:
  using Node = Np;
  using T = typename Node::T;
  using F = function< T(T, T) >;
  using S = function< T(T) >;
  using super = SplayTreeBase< Node >;
  using NP = typename super::NP;

  explicit ReversibleSplayTree(const F &f, const S &s, const T &M1) :
      f(f), s(s), M1(M1) {}

  using super::splay;
  using super::split;
  using super::count;
  using super::merge;
  using super::build_node;
  using super::insert_node;

  inline const T &sum(const NP t) { return t ? t->sum : M1; }

  NP alloc(const T &x) { return new Node(x); }

  T query(NP &t, int a, int b) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, y.first, y.second);
    return ret;
  }

  NP build(const vector< T > &v) {
    vector< NP > vs(v.size());
    for(int i = 0; i < v.size(); i++) vs[i] = alloc(v[i]);
    return build_node(vs);
  }

  void toggle(NP t) {
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  NP update(NP t) override {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  void push(NP t) override {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  NP insert(NP t, int k, const T &x) {
    return insert_node(t, k, alloc(x));
  }

  NP set_element(NP t, int k, const T &x) {
    splay(t);
    return imp_set_element(t, k, x);
  }

  pair< NP , NP > split_lower_bound(NP t, const T &key) {
    if(!t) return {nullptr, nullptr};
    push(t);
    if(key <= t->key) {
      auto x = split_lower_bound(t->l, key);
      t->l = x.second;
      t->p = nullptr;
      if(x.second) x.second->p = t;
      return {x.first, update(t)};
    } else {
      auto x = split_lower_bound(t->r, key);
      t->r = x.first;
      t->p = nullptr;
      if(x.first) x.first->p = t;
      return {update(t), x.second};
    }
  }

private:
  const T M1;
  const F f;
  const S s;

  NP imp_set_element(NP t, int k, const T &x) {
    push(t);
    if(k < count(t->l)) {
      return imp_set_element(t->l, k, x);
    } else if(k == count(t->l)) {
      t->key = x;
      splay(t);
      return t;
    } else {
      return imp_set_element(t->r, k - count(t->l) - 1, x);
    }
  }
};

template< typename T >
using RST = ReversibleSplayTree< ReversibleSplayTreeNode< T > >;
