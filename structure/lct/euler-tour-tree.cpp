/**
 * @brief Euler-Tour-Tree
 */
template< typename T >
struct EulerTourTree {

private:

  struct Node {
    Node *l, *r, *p;
    size_t sz;

    explicit Node() : sz(1), l(nullptr), r(nullptr), p(nullptr) {}

    bool is_root() const {
      return not p or (p->l != this and p->r != this);
    }
  };

  using NP = Node *;

  NP update(NP t) {
    t->sz = 1;
    if(t->l) t->sz += t->l->sz;
    if(t->r) t->sz += t->r->sz;
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

  void splay(NP t) {
    while(not t->is_root()) {
      NP q = t->p;
      if(q->is_root()) {
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        NP r = q->p;
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

  NP splay_front(NP t) {
    splay(t);
    while(t->l) t = t->l;
    splay(t);
    return t;
  }

  NP splay_back(NP t) {
    splay(t);
    while(t->r) t = t->r;
    splay(t);
    return t;
  }

  template< typename... Args >
  NP merge(NP p, Args... args) {
    return merge(p, merge(args...));
  }

  NP merge(NP l, NP r) {
    if(!l && !r) return nullptr;
    if(!l) return splay(r), r;
    if(!r) return splay(l), l;
    splay(l), splay(r);
    l = splay_back(l);
    l->r = r;
    r->p = l;
    update(l);
    return l;
  }


  NP alloc() {
    return new Node();
  }

  NP reroot(NP t) {
    splay(t);
    NP l = t->l;
    if(not l) return t;
    t->l = nullptr;
    update(t);
    return merge(l, t);
  }

  NP link(NP u, NP v, NP e1, NP e2) {
    u = reroot(u);
    v = reroot(v);
    return merge(u, e1, v, e2);
  }

  NP cut(NP e1, NP e2) {
    splay(e1);
    splay(e2);
    NP p = e1->p;
    bool is_r;
    if(p != e2) {
      is_r = p == e2->r;
      p->p = nullptr;
      if(e1 == p->l) rotr(e1);
      else rotl(e1);
    } else {
      is_r = e1 == e2->r;
    }
    if(e1->l) {
      e1->l->p = nullptr;
    }
    if(e1->r) {
      e1->r->p = nullptr;
    }
    if(is_r) {
      if(e2->l) e2->l->p = nullptr;
      return merge(e2->l, e1->r);
    } else {
      if(e2->r) e2->r->p = nullptr;
      return merge(e1->l, e2->r);
    }
  }

  bool is_connected(NP u, NP v) {
    splay(u);
    splay(v);
    return u->p != nullptr;
  }

  vector< unordered_map< int, NP > > ptr;

  NP get_node(int l, int r) {
    if(ptr[l].find(r)) {
      ptr[l][r] = alloc();
    }
    return ptr[l][r];
  }

public:
  EulerTourTree() = default;

  explicit EulerTourTree(int n) : ptr(n) {}

  void reroot(int k) {
    reroot(get_node(k, k));
  }

  void link(int u, int v) {
    ptr[u][v] = alloc();
    ptr[v][u] = alloc();
    link(get_node(u, u), get_node(v, v), ptr[u][v], ptr[v][u]);
  }

  void cut(int u, int v) {
    auto it1 = ptr[u].find(v);
    auto it2 = ptr[v].find(u);
    cut(it1, it2);
    ptr[u].erase(it1);
    ptr[v].erase(it2);
  }

  bool is_conneced(int u, int v) {
    return is_connected(get_node(u, u), get_node(v, v));
  }
};
