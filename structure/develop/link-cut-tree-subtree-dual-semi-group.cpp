template< typename T, typename E, typename OpTT, typename OpTE, typename OpEE, size_t V >
struct LinkCutTreeSubtreeDualSemiGroup {

  struct Node {
    Node *l, *r, *p;

    typename DualSplayTree< E, OpEE, V >::Node *light, *belong;
    T key;
    T sum;

    E lazy;

    bool rev;

    Node() = default;

    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }

    Node(const T &key, const E &lazy) :
        key(key), sum(key), lazy(lazy), rev(false), belong(nullptr),
        l(nullptr), r(nullptr), p(nullptr), light(nullptr) {}
  };

  DualSplayTree< E, OpEE, V > st;
  const E e0;
  const OpTT f;
  const OpTE g;
  const OpEE h;
  ArrayPool< Node, V > pool;

  LinkCutTreeSubtreeDualSemiGroup(const OpTT &f, const OpTE &g, const OpEE &h, const E &e0)
      : st(h, e0), f(f), g(g), h(h), e0(e0), pool() {}

  Node *alloc(const T &key) {
    auto ret = &(*pool.alloc() = Node(key, e0));
    return ret;
  }

  Node *set_key(Node *t, const T &key) {
    expose(t);
    t->key = key;
    update(t);
    return t;
  }

  void toggle(Node *t) {
    swap(t->l, t->r);
    t->rev ^= true;
  }

  void propagate(Node *t, const E &x) {
    t->lazy = h(t->lazy, x);
    st.set_propagate(t->light, x);
    t->key = g(t->key, x);
    t->sum = g(t->sum, x);
  }

  void push(Node *t) {
    if(t->lazy != e0) {
      if(t->l) propagate(t->l, t->lazy);
      if(t->r) propagate(t->r, t->lazy);
      t->lazy = e0;
    }
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(Node *t) {
    t->sum = t->key;
    if(t->l) t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sum = f(t->sum, t->r->sum);
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

    Node *rot = t;
    while(!rot->is_root()) rot = rot->p;
    t->belong = rot->belong;
    if(t != rot) rot->belong = nullptr;

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
    for(auto *cur = t; cur; cur = cur->p) {
      splay(cur);
      if(cur->r) {
        cur->light = st.push_back(cur->light, e0);
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if(cur->r) {
        st.splay(cur->r->belong);
        propagate(cur->r, cur->r->belong->val);
        push(cur->r);
        cur->light = st.erase(cur->r->belong);
      }
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

  void subtree_add(Node *t, const E &x) {
    expose(t);
    st.set_propagate(t->light, x);
    t->key = g(t->key, x);
    if(t->r) {
      propagate(t->r, x);
      push(t->r);
    }
    update(t);
  }

  void component_add(Node *t, const E &x) {
    expose(t);
    propagate(t, x);
    push(t);
  }
};


template< typename T, typename E, size_t V, typename OpTT, typename OpTE, typename OpEE >
LinkCutTreeSubtreeDualSemiGroup< T, E, OpTT, OpTE, OpEE, V > get_link_cut_tree_subtree_dual_semi_group(const OpTT &f, const OpTE &g, const OpEE &h, const E &e0) {
  return LinkCutTreeSubtreeDualSemiGroup< T, E, OpTT, OpTE, OpEE, V >(f, g, h, e0);
}
