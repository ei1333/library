/**
 * @brief Link Cut Tree
 * 
 */
template< typename T, typename F, typename S >
struct LinkCutTree {

private:
  F f;
  S s;

  struct Node {
    Node *l, *r, *p;
    T key, sum;
    bool rev;
    size_t sz;

    explicit Node(const T &v) : key(v), sum(v), sz(1), rev(false),
                                l(nullptr), r(nullptr), p(nullptr) {}

    bool is_root() const {
      return not p or (p->l != this and p->r != this);
    }
  };

public:
  using NP = Node *;

private:
  NP update(NP t) {
    t->sz = 1;
    t->sum = t->key;
    if(t->l) t->sz += t->l->sz, t->sum = f(t->l->sum, t->sum);
    if(t->r) t->sz += t->r->sz, t->sum = f(t->sum, t->r->sum);
    return t;
  }

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
      update(y);
    }
  }

  void toggle(NP t) {
    swap(t->l, t->r);
    t->sum = s(t->sum);
    t->rev ^= true;
  }

  void push(NP t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void splay(NP t) {
    push(t);
    while(not t->is_root()) {
      NP q = t->p;
      if(q->is_root()) {
        push(q), push(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        NP r = q->p;
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

public:
  LinkCutTree(const F &f, const S &s) : f(f), s(s) {}

  NP alloc(const T &v = T()) {
    return new Node(v);
  }

  vector< NP > build(vector< T > &vs) {
    vector< NP > nodes(vs.size());
    for(int i = 0; i < (int) vs.size(); i++) {
      nodes[i] = alloc(vs[i]);
    }
    return nodes;
  }

  NP expose(NP t) {
    NP rp = nullptr;
    for(NP cur = t; cur; cur = cur->p) {
      splay(cur);
      cur->r = rp;
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void evert(NP t) {
    expose(t);
    toggle(t);
    push(t);
  }

  void link(NP child, NP parent) {
    if(is_connected(child, parent)) {
      throw runtime_error("child and parent must be different connected components");
    }
    if(child->l) {
      throw runtime_error("child must be root");
    }
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(NP child) {
    expose(child);
    NP parent = child->l;
    if(not parent) {
      throw runtime_error("child must not be root");
    }
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  bool is_connected(NP u, NP v) {
    expose(u), expose(v);
    return u == v or u->p;
  }

  NP lca(NP u, NP v) {
    if(not is_connected(u, v)) return nullptr;
    expose(u);
    return expose(v);
  }

  NP get_kth(NP x, int k) {
    expose(x);
    while(x) {
      push(x);
      if(x->r && x->r->sz > k) {
        x = x->r;
      } else {
        if(x->r) k -= x->r->sz;
        if(k == 0) {
          splay(x);
          return x;
        }
        k -= 1;
        x = x->l;
      }
    }
    return nullptr;
  }

  const T &query(NP u) {
    expose(u);
    return u->sum;
  }

  const T &query(NP u, NP v) {
    evert(u);
    return query(v);
  }

  void set_key(NP t, T v) {
    expose(t);
    t->key = v;
    update(t);
  }
};

template< typename T, typename F, typename S >
LinkCutTree< T, F, S > get_link_cut_tree(const F &f, const S &s) {
  return {f, s};
}
