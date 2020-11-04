#include "splay-tree.cpp"

template< typename T, size_t V >
struct LinkCutTreeSubTree {
  using key_t = typename T::key_t;
  using heavy_t = typename T::heavy_t;
  using light_t = typename T::light_t;

  struct Node {
    Node *l, *r, *p;

    typename SplayTree< light_t, V >::Node *light, *belong;
    heavy_t sum;

    Node() = default;

    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }

    Node(const key_t &key) :
        belong(nullptr), l(nullptr), r(nullptr), p(nullptr), light(nullptr) {
      sum.set_key(key);
    }
  };

  using ST = SplayTree< light_t, V >;

  ST st;
  const heavy_t ident;
  ArrayPool< Node, V > pool;

  LinkCutTreeSubTree() : ident(heavy_t()), st(), pool() {}

  Node *alloc(const key_t &key) {
    auto ret = &(*pool.alloc() = Node(key));
    update(ret);
    return ret;
  }

  Node *set_key(Node *t, const key_t &key) {
    expose(t);
    t->sum.set_key(key);
    update(t);
    return t;
  }

  void update(Node *t) {
    t->sum.update(t->l ? t->l->sum : ident, t->r ? t->r->sum : ident, st.sum(t->light));
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

    Node *rot = t;
    while(!rot->is_root()) rot = rot->p;
    t->belong = rot->belong;
    if(t != rot) rot->belong = nullptr;

    while(!t->is_root()) {
      auto *q = t->p;
      if(q->is_root()) {
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


  Node *expose(Node *t) {
    Node *rp = nullptr;
    for(auto *cur = t; cur; cur = cur->p) {
      splay(cur);
      if(cur->r) {
        cur->light = st.push_back(cur->light, cur->r->sum.add());
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if(cur->r) {
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

  Node *lca(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return nullptr;
    expose(u);
    return expose(v);
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
