template< typename Monoid = int, typename OperatorMonoid = Monoid >
struct LinkCutTree {
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;
  using S = function< Monoid(Monoid) >;

  struct Node {
    Node *l, *r, *p;
    int idx;
    Monoid key, sum;
    OperatorMonoid lazy;

    bool rev;
    int sz;

    bool is_root() {
      return !p || (p->l != this && p->r != this);
    }

    Node(int idx, const Monoid &key, const OperatorMonoid &om) :
        idx(idx), key(key), sum(key), lazy(om), sz(1),
        l(nullptr), r(nullptr), p(nullptr), rev(false) {}
  };

  const Monoid M1;
  const OperatorMonoid OM0;
  const F f;
  const G g;
  const H h;
  const S s;

  LinkCutTree() : LinkCutTree([](Monoid a, Monoid b) { return a + b; }, [](Monoid a) { return a; }, Monoid()) {}

  LinkCutTree(const F &f, const S &s, const Monoid &M1) :
      LinkCutTree(f, G(), H(), s, M1, OperatorMonoid()) {}

  LinkCutTree(const F &f, const G &g, const H &h, const S &s,
              const Monoid &M1, const OperatorMonoid &OM0) :
      f(f), g(g), h(h), s(s), M1(M1), OM0(OM0) {}

  Node *make_node(int idx, const Monoid &v = Monoid()) {
    return new Node(idx, v, OM0);
  }

  void propagate(Node *t, const OperatorMonoid &x) {
    t->lazy = h(t->lazy, x);
    t->key = g(t->key, x);
    t->sum = g(t->sum, x);
  }

  void toggle(Node *t) {
    assert(t);
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  void push(Node *t) {
    if(t->lazy != OM0) {
      if(t->l) propagate(t->l, t->lazy);
      if(t->r) propagate(t->r, t->lazy);
      t->lazy = OM0;
    }
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(Node *t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
  }

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

  void splay(Node *t) {
    push(t);
    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
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

  Node *expose(Node *t) {
    Node *rp = nullptr;
    for(Node *cur = t; cur; cur = cur->p) {
      splay(cur);
      cur->r = rp;
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void link(Node *child, Node *parent) {
    expose(child);
    expose(parent);
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(Node *child) {
    expose(child);
    auto *parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(Node *t) {
    expose(t);
    toggle(t);
    push(t);
  }

  Node *lca(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
  }

  vector< int > get_path(Node *x) {
    vector< int > vs;
    function< void(Node *) > dfs = [&](Node *cur) {
      if(!cur) return;
      push(cur);
      dfs(cur->r);
      vs.push_back(cur->idx);
      dfs(cur->l);
    };
    expose(x);
    dfs(x);
    return vs;
  }

  void set_propagate(Node *t, const OperatorMonoid &x) {
    expose(t);
    propagate(t, x);
    push(t);
  }

  Node *get_kth(Node *x, int k) {
    expose(x);
    while(x) {
      push(x);
      if(x->r && x->r->sz > k) {
        x = x->r;
      } else {
        if(x->r) k -= x->r->sz;
        if(k == 0) return x;
        k -= 1;
        x = x->l;
      }
    }
    return nullptr;
  }

  Node *get_root(Node *x) {
    expose(x);
    while(x->l) {
      push(x);
      x = x->l;
    }
    return x;
  }
};
