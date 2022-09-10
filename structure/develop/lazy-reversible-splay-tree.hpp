/**
 * @brief Lazy-Reversible-Splay-Tree(遅延伝搬反転可能Splay木)
 */
template< typename Tp, typename Ep >
struct LazyReversibleSplayTreeNode {
  using T = Tp;
  using E = Ep;
  LazyReversibleSplayTreeNode *l, *r, *p;
  T key, sum;
  E lazy;
  bool rev;
  size_t sz;

  LazyReversibleSplayTreeNode() : LazyReversibleSplayTreeNode(Tp()) {}

  LazyReversibleSplayTreeNode(const T &key) :
      LazyReversibleSplayTreeNode(key, E()) {}

  LazyReversibleSplayTreeNode(const T &key, const E &lazy) :
      key(key), sum(key), rev(false), l(nullptr), r(nullptr), p(nullptr), sz(1), lazy(lazy) {}
};

template< typename Np >
struct LazyReversibleSplayTree : ReversibleSplayTree< Np > {
public:
public:
  using Node = Np;
  using T = typename Node::T;
  using E = typename Node::E;
  using super = ReversibleSplayTree< Node >;
  using F = typename super::F;
  using G = function< T(T, E) >;
  using H = function< E(E, E) >;
  using S = typename super::S;
  using NP = typename super::NP;

  explicit LazyReversibleSplayTree(const F &f, const G &g, const H &h, const S &s,
                                   const T &M1, const E &OM0) :
      g(g), h(h), OM0(OM0), super(f, s, M1) {}


  using super::splay;
  using super::split;
  using super::merge;

  NP alloc(const T &x) { return new Node(x, OM0); }

  void push(NP t) override {
    if(t->lazy != OM0) {
      if(t->l) propagate(t->l, t->lazy);
      if(t->r) propagate(t->r, t->lazy);
      t->lazy = OM0;
    }
    super::push(t);
  }

  NP set_propagate(NP& t, int a, int b, const E &pp) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    set_propagate(y.first, pp);
    return t = merge(x.first, y.first, y.second);
  }

  void set_propagate(NP t, const E &pp) {
    splay(t);
    propagate(t, pp);
    push(t);
  }

private:
  const E OM0;
  const G g;
  const H h;

  void propagate(NP t, const E &x) {
    t->lazy = h(t->lazy, x);
    t->key = g(t->key, x);
    t->sum = g(t->sum, x);
  }
};

template< typename T, typename E >
using LRST = LazyReversibleSplayTree< LazyReversibleSplayTreeNode< T, E > >;
