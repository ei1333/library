template <typename TreeDPInfo>
struct LazySplayTreeForDashedEdge {
  using Lazy = typename TreeDPInfo::Lazy;
  using Point = typename TreeDPInfo::Point;
  struct Node {
    Node *l, *r, *p;
    Point key, sum;
    Lazy lazy, lbuf;

    explicit Node(const Point &key)
        : key(key),
          sum(key),
          lazy(Lazy()),
          lbuf(Lazy()),
          l(nullptr),
          r(nullptr),
          p(nullptr) {}
  };

  LazySplayTreeForDashedEdge() = default;

  using NP = Node *;

  void rotr(NP t) const {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void rotl(NP t) const {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void update(NP t) const {
    t->sum = t->key;
    if (t->l) t->sum = TreeDPInfo::rake(t->sum, t->l->sum);
    if (t->r) t->sum = TreeDPInfo::rake(t->sum, t->r->sum);
  }

  NP get_right(NP t) const {
    while (t->r) t = t->r;
    return t;
  }

  NP alloc(const Point &v) const {
    auto t = new Node(v);
    update(t);
    return t;
  }

  void propagate(NP t, const Lazy &lazy) const {
    t->key.propagate(lazy);
    t->sum.propagate(lazy);
    t->lbuf.propagate(lazy);
    t->lazy.propagate(lazy);
  }

  void push(NP t) const {
    if (t->l) propagate(t->l, t->lazy);
    if (t->r) propagate(t->r, t->lazy);
    t->lazy = Lazy();
  }

  void splay(NP t) const {
    push(t);
    while (t->p) {
      NP q = t->p;
      if (!q->p) {
        if (q->l == t)
          rotr(t);
        else
          rotl(t);
      } else {
        NP r = q->p;
        if (r->l == q) {
          if (q->l == t)
            rotr(q), rotr(t);
          else
            rotl(t), rotr(t);
        } else {
          if (q->r == t)
            rotl(q), rotl(t);
          else
            rotr(t), rotl(t);
        }
      }
    }
  }

  NP insert(NP t, const Point &v) const {
    if (not t) {
      t = alloc(v);
      return t;
    } else {
      NP cur = get_right(t), z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->r = z;
      update(cur);
      splay(z);
      return z;
    }
  }

  NP erase(NP t) const {
    splay(t);
    NP x = t->l, y = t->r;
    delete t;
    if (not x) {
      t = y;
      if (t) t->p = nullptr;
    } else if (not y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
      update(t);
    }
    return t;
  }
};

template <typename TreeDPInfo>
struct LazyTopTree {
  using Lazy = typename TreeDPInfo::Lazy;
  using Path = typename TreeDPInfo::Path;
  using Info = typename TreeDPInfo::Info;

 private:
  struct Node {
    Node *l, *r, *p;
    Info info;
    Path sum, mus;
    typename LazySplayTreeForDashedEdge<TreeDPInfo>::Node *light, *belong;
    bool rev;
    Lazy hlazy, llazy;

    bool is_root() const { return not p or (p->l != this and p->r != this); }

    Node(const Info &info)
        : info(info),
          l(nullptr),
          r(nullptr),
          p(nullptr),
          rev(false),
          light(nullptr),
          belong(nullptr),
          hlazy(Lazy()),
          llazy(Lazy()) {}
  };

 public:
  using NP = Node *;
  const LazySplayTreeForDashedEdge<TreeDPInfo> splay_tree;

 private:
  void toggle(NP t) {
    swap(t->l, t->r);
    swap(t->sum, t->mus);
    t->rev ^= true;
  }

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void propagate_heavy(NP t, const Lazy &hlazy) {
    t->hlazy.propagate(hlazy);
    t->info.propagate(hlazy);
    t->sum.propagate(hlazy);
    t->mus.propagate(hlazy);
  }

  void propagate_light(NP t, const Lazy &llazy) {
    t->llazy.propagate(llazy);
    t->sum.propagate_light(llazy);
    t->mus.propagate_light(llazy);
  }

  void propagate_all(NP t, const Lazy &lazy) {
    propagate_heavy(t, lazy);
    propagate_light(t, lazy);
  }

 public:
  LazyTopTree() : splay_tree{} {}

  void push(NP t) {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
    {
      if (t->l) {
        propagate_heavy(t->l, t->hlazy);
        propagate_light(t->l, t->llazy);
      }
      if (t->r) {
        propagate_heavy(t->r, t->hlazy);
        propagate_light(t->r, t->llazy);
      }
      if (t->light) {
        splay_tree.propagate(t->light, t->llazy);
      }
      t->hlazy = Lazy();
      t->llazy = Lazy();
    }
  }

  void push_rev(NP t) {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(NP t) {
    Path key = t->light ? TreeDPInfo::add_vertex(t->light->sum, t->info)
                        : TreeDPInfo::vertex(t->info);
    t->sum = key;
    t->mus = key;
    if (t->l) {
      t->sum = TreeDPInfo::compress(t->l->sum, t->sum);
      t->mus = TreeDPInfo::compress(t->mus, t->l->mus);
    }
    if (t->r) {
      t->sum = TreeDPInfo::compress(t->sum, t->r->sum);
      t->mus = TreeDPInfo::compress(t->r->mus, t->mus);
    }
  }

  void splay(NP t) {
    push(t);
    {
      NP rot = t;
      while (not rot->is_root()) rot = rot->p;
      t->belong = rot->belong;
      if (t != rot) rot->belong = nullptr;
    }
    while (not t->is_root()) {
      NP q = t->p;
      if (q->is_root()) {
        push_rev(q), push_rev(t);
        if (q->l == t)
          rotr(t);
        else
          rotl(t);
      } else {
        NP r = q->p;
        push_rev(r), push_rev(q), push_rev(t);
        if (r->l == q) {
          if (q->l == t)
            rotr(q), rotr(t);
          else
            rotl(t), rotr(t);
        } else {
          if (q->r == t)
            rotl(q), rotl(t);
          else
            rotr(t), rotl(t);
        }
      }
    }
  }

  NP expose(NP t) {
    NP rp = nullptr;
    for (NP cur = t; cur; cur = cur->p) {
      splay(cur);
      if (cur->r) {
        cur->light =
            splay_tree.insert(cur->light, TreeDPInfo::add_edge(cur->r->sum));
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if (cur->r) {
        splay_tree.splay(cur->r->belong);
        propagate_all(cur->r, cur->r->belong->lbuf);
        push(cur->r);
        cur->light = splay_tree.erase(cur->r->belong);
      }
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void link(NP child, NP parent) {
    if (is_connected(child, parent)) {
      throw runtime_error(
          "child and parent must be different connected components");
    }
    if (child->l) {
      throw runtime_error("child must be root");
    }
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(NP child) {
    expose(child);
    NP parent = child->l;
    if (not parent) {
      throw runtime_error("child must not be root");
    }
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(NP t) {
    expose(t);
    toggle(t);
    push(t);
  }

  NP alloc(const Info &v) {
    NP t = new Node(v);
    update(t);
    return t;
  }

  bool is_connected(NP u, NP v) {
    expose(u), expose(v);
    return u == v or u->p;
  }

  vector<NP> build(vector<Info> &vs) {
    vector<NP> nodes(vs.size());
    for (int i = 0; i < (int)vs.size(); i++) {
      nodes[i] = alloc(vs[i]);
    }
    return nodes;
  }

  NP lca(NP u, NP v) {
    if (not is_connected(u, v)) return nullptr;
    expose(u);
    return expose(v);
  }

  void set_key(NP t, const Info &v) {
    expose(t);
    t->info = move(v);
    update(t);
  }

  void set_propagate_path(NP t, const Lazy &lazy) {
    expose(t);
    propagate_heavy(t, lazy);
    push(t);
    update(t);
  }

  void set_propagate_path(NP u, NP v, const Lazy &lazy) {
    evert(u);
    set_propagate_path(v, lazy);
  }

  void set_propagate_all(NP t, const Lazy &lazy) {
    expose(t);
    propagate_all(t, lazy);
    push(t);
    update(t);
  }

  void set_propagate_subtree(NP t, const Lazy &lazy) {
    expose(t);
    NP l = t->l;
    t->l = nullptr;
    propagate_all(t, lazy);
    push(t);
    t->l = l;
    update(t);
  }

  void set_propagate_subtree(NP r, NP u, const Lazy &lazy) {
    evert(r);
    set_propagate_subtree(u, lazy);
  }

  const Path &query(NP u) {
    evert(u);
    return u->sum;
  }

  const Path &query_path(NP u) {
    expose(u);
    return u->sum;
  }

  const Path &query_path(NP u, NP v) {
    evert(u);
    return query_path(v);
  }

  Path query_subtree(NP u) {
    expose(u);
    NP l = u->l;
    u->l = nullptr;
    update(u);
    auto ret = u->sum;
    u->l = l;
    update(u);
    return ret;
  }

  Path query_subtree(NP r, NP u) {
    evert(r);
    return query_subtree(u);
  }
};

/*
struct TreeDPInfo {
  struct Lazy {
    Lazy() : {}
    Lazy(T v): {}
    void propagate(const Lazy &p) {}
  };
  struct Point {
    void propagate(const Lazy &p) {}
  };
  struct Path {
    void propagate(const Lazy& p) {}
    void propagate_light(const Lazy& p) {}
  };
  struct Info {
    void propagate(const Lazy& p) {}
  };

  static Path vertex(const Info& u) {}
  static Path add_vertex(const Point& d, const Info& u) {}
  static Point add_edge(const Path& d) {}
  static Point rake(const Point& l, const Point& r) {}
  static Path compress(const Path& p, const Path& c) {}
};
*/
