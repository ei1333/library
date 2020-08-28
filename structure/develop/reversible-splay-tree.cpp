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

  explicit ReversibleSplayTree(const F &f, const S &s, const T &M1) :
      f(f), s(s), M1(M1) {}

  using super::splay;
  using super::split;
  using super::count;
  using super::merge;
  using super::build_node;
  using super::push_back_node;
  using super::push_front_node;
  using super::insert_node;

  inline const T &sum(const Node *t) { return t ? t->sum : M1; }

  virtual Node *alloc(const T &x) { return new Node(x); }

  T query(Node *&t, int a, int b) {
    splay(t);
    auto x = split(t, a);
    auto y = split(x.second, b - a);
    auto ret = sum(y.first);
    t = merge(x.first, y.first, y.second);
    return ret;
  }

  virtual Node *build(const vector< T > &v) {
    vector< Node * > vs(v.size());
    for(int i = 0; i < v.size(); i++) vs[i] = new Node(v[i]);
    return build_node(vs);
  }

  void toggle(Node *t) {
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  Node *update(Node *t) override {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  void push(Node *t) override {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void set_element(Node *&t, int k, const T &x) {
    splay(t);
    sub_set_element(t, k, x);
  }

  virtual Node *push_front(Node *t, const T &x) {
    return push_front_node(t, new Node(x));
  }

  virtual Node *push_back(Node *t, const T &x) {
    return push_back_node(t, new Node(x));
  }

  virtual void insert(Node *&t, int k, const T &x) {
    insert_node(t, k, new Node(x));
  }

private:
  const T M1;
  const F f;
  const S s;

  Node *sub_set_element(Node *&t, int k, const T &x) {
    push(t);
    if(k < count(t->l)) {
      return sub_set_element(t->l, k, x);
    } else if(k == count(t->l)) {
      t->key = x;
      splay(t);
      return t;
    } else {
      return sub_set_element(t->r, k - count(t->l) - 1, x);
    }
  }
};

template< typename T >
using RST = ReversibleSplayTree< ReversibleSplayTreeNode< T > >;
