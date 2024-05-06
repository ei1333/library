template <typename TreeDPInfo>
struct SplayTreeForDashedEdge {
  using Point = typename TreeDPInfo::Point;
  struct Node {
    Node *l, *r, *p;
    Point key, sum;

    explicit Node(const Point &key)
        : key(key),
          sum(key),
          l(nullptr),
          r(nullptr),
          p(nullptr) {}
  };

  SplayTreeForDashedEdge() = default;

  using NP = Node *;

  void rotr(NP t) const {
    NP x = t->p, y = x->p;
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
    if(t->l) t->sum = TreeDPInfo::rake(t->sum, t->l->sum);
    if(t->r) t->sum = TreeDPInfo::rake(t->sum, t->r->sum);
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

  void splay(NP t) const {
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
struct TopTree {
  using Path = typename TreeDPInfo::Path;
  using Info = typename TreeDPInfo::Info;

private:
  struct Node {
    Node *l, *r, *p;
    Info info;
    Path sum, mus;
    typename SplayTreeForDashedEdge<TreeDPInfo>::Node *light, *belong;
    bool rev;

    bool is_root() const { return not p or (p->l != this and p->r != this); }

    Node(const Info &info)
        : info(info),
          l(nullptr),
          r(nullptr),
          p(nullptr),
          rev(false),
          light(nullptr),
          belong(nullptr) {}
  };

public:
  using NP = Node *;
  const SplayTreeForDashedEdge<TreeDPInfo> splay_tree;

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

public:
  TopTree() : splay_tree{} {}

  void push(NP t) {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
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
    Path key = t->light ? TreeDPInfo::add_vertex(t->light->sum, t->info) : TreeDPInfo::vertex(t->info);
    t->sum = key;
    t->mus = key;
    if(t->l) {
      t->sum = TreeDPInfo::compress(t->l->sum, t->sum);
      t->mus = TreeDPInfo::compress(t->mus, t->l->mus);
    }
    if(t->r) {
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
        cur->light = splay_tree.insert(cur->light, TreeDPInfo::add_edge(cur->r->sum));
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if (cur->r) {
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
    expose(parent);
    expose(child);
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(NP child) {
    expose(child);
    NP parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(NP t) {
    expose(t);
    toggle(t);
    push(t);
  }

  NP alloc(const Info& v) {
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
    t->info = std::move(v);
    update(t);
  }

  const Path &query(NP u) {
    evert(u);
    return u->sum;
  }

  const Path &query_path(NP u, NP v) {
    evert(u);
    expose(v);
    return v->sum;
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

template <typename TreeDPInfo>
struct TopTreeBuilder : TopTree< TreeDPInfo > {
private:
  using TT = TopTree< TreeDPInfo >;
  using Info = typename TreeDPInfo::Info;
  using TT::alloc;
  using TT::link;

  int n, e_sz;
  vector< vector< pair< int, int > > > g;

public:
  vector< typename TT::NP > vs, es;

  explicit TopTreeBuilder(int n) : n(n), g(n), vs(n), es(n), e_sz(0) {}

  void set_vertex(int u, const Info& info) {
    assert(0 <= u and u < n);
    vs[u] = this->alloc(info);
  }

  void add_edge(int u, int v, const Info& info, int id = -1) {
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    assert(u != v);
    if(id == -1) id = e_sz++;
    assert(0 <= id and id < n);
    g[u].emplace_back(v, id);
    g[v].emplace_back(u, id);
    es[id] = alloc(info);
  }

  void build(int r = 0) {
    vector< pair< int, int > > que;
    que.reserve(n);
    que.emplace_back(r, -1);
    while(not que.empty()) {
      auto [u, p] = que.back();
      que.pop_back();
      for(auto& [v, id] : g[u]) {
        if(v == p) continue;
        que.emplace_back(v, u);
        link(es[id], vs[u]);
        link(vs[v], es[id]);
      }
    }
  }
};

/*
struct TreeInfo {
  struct Point {};
  struct Path {};
  struct Info {};
  static Path vertex(const Info& u) {}
  static Path add_vertex(const Point& d, const Info& u) {}
  static Point add_edge(const Path& d) {}
  static Point rake(const Point& l, const Point& r) {}
  static Path compress(const Path& p, const Path& c) {}
};
*/
