/**
 * @brief 何でもできるLCT
 */
template< typename LInfo, typename Lazy >
struct SplayTree {
  struct Node {
    Node *l, *r, *p;
    LInfo info;
    Lazy lazy, lbuf;

    explicit Node(const LInfo &info) : info(info), l(nullptr), r(nullptr),
                                       p(nullptr), lazy(Lazy()), lbuf(Lazy()) {}
  };

  const LInfo e;

  SplayTree() : e(LInfo()) {}

  using NP = Node *;

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  const LInfo &get_info(NP t) {
    return t ? t->info : e;
  }

  void update(NP t) {
    t->info.update(get_info(t->l), get_info(t->r));
  }

  NP get_right(NP t) {
    while(t->r) t = t->r;
    return t;
  }

  NP alloc(const LInfo &v) {
    auto t = new Node(v);
    update(t);
    return t;
  }

  void propagate(NP t, const Lazy &lazy) {
    t->info.propagate(lazy);
    t->lbuf.propagate(lazy);
    t->lazy.propagate(lazy);
  }

  void push(NP t) {
    if(t->l) propagate(t->l, t->lazy);
    if(t->r) propagate(t->r, t->lazy);
    t->lazy = Lazy();
  }

  void splay(NP t) {
    push(t);
    while(t->p) {
      NP q = t->p;
      if(!q->p) {
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

  NP insert(NP t, const LInfo &v) {
    if(not t) {
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

  NP erase(NP t) {
    splay(t);
    NP x = t->l, y = t->r;
    delete t;
    if(not x) {
      t = y;
      if(t) t->p = nullptr;
    } else if(not y) {
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

template< template< typename, typename > typename _Info,
    template< typename > typename _LInfo, typename Lazy >
struct SuperLinkCutTree {
  using LInfo = _LInfo< Lazy >;
  using Info = _Info< LInfo, Lazy >;

private:
  struct Node {
    Node *l, *r, *p;
    Info info;
    typename SplayTree< LInfo, Lazy >::Node *light, *belong;
    bool rev;
    Lazy hlazy, llazy;

    bool is_root() const {
      return not p or (p->l != this and p->r != this);
    }

    explicit Node(const Info &info)
        : info(info), l(nullptr), r(nullptr), p(nullptr), rev(false),
          light(nullptr), belong(nullptr), hlazy(Lazy()), llazy(Lazy()) {}
  };

public:
  using NP = Node *;
  SplayTree< LInfo, Lazy > splay_tree;

private:
  const Info e;

private:
  void toggle(NP t) {
    swap(t->l, t->r);
    t->info.toggle();
    t->rev ^= true;
  }

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if((t->p = y)) {
      if(y->l == x) y->l = t;
      if(y->r == x) y->r = t;
    }
  }

  void propagate_heavy(NP t, const Lazy &hlazy) {
    t->hlazy.propagate(hlazy);
    t->info.propagate(hlazy);
  }

  void propagate_light(NP t, const Lazy &llazy) {
    t->llazy.propagate(llazy);
    t->info.propagate_light(llazy);
  }

  void propagate_all(NP t, const Lazy &lazy) {
    propagate_heavy(t, lazy);
    propagate_light(t, lazy);
  }

public:
  SuperLinkCutTree() : e{Info()}, splay_tree{} {}

  void push(NP t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
    {
      if(t->l) {
        propagate_heavy(t->l, t->hlazy);
        propagate_light(t->l, t->llazy);
      }
      if(t->r) {
        propagate_heavy(t->r, t->hlazy);
        propagate_light(t->r, t->llazy);
      }
      if(t->light) {
        splay_tree.propagate(t->light, t->llazy);
      }
      t->hlazy = Lazy();
      t->llazy = Lazy();
    }
  }

  void push_rev(NP t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }

  const Info &get_info(NP t) {
    return t ? t->info : e;
  }

  void update(NP t) {
    t->info.update(get_info(t->l), get_info(t->r), splay_tree.get_info(t->light));
  }

  void splay(NP t) {
    push(t);
    {
      NP rot = t;
      while(not rot->is_root()) rot = rot->p;
      t->belong = rot->belong;
      if(t != rot) rot->belong = nullptr;
    }
    while(not t->is_root()) {
      NP q = t->p;
      if(q->is_root()) {
        push_rev(q), push_rev(t);
        if(q->l == t) rotr(t);
        else rotl(t);
      } else {
        NP r = q->p;
        push_rev(r), push_rev(q), push_rev(t);
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

  NP expose(NP t) {
    NP rp = nullptr;
    for(NP cur = t; cur; cur = cur->p) {
      splay(cur);
      if(cur->r) {
        cur->light = splay_tree.insert(cur->light, cur->r->info.link());
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if(cur->r) {
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

  NP alloc(const Info &info) {
    NP t = new Node(info);
    update(t);
    return t;
  }

  bool is_connected(NP u, NP v) {
    expose(u), expose(v);
    return u == v or u->p;
  }

  vector< NP > build(vector< Info > &vs) {
    vector< NP > nodes(vs.size());
    for(int i = 0; i < (int) vs.size(); i++) {
      nodes[i] = alloc(vs[i]);
    }
    return nodes;
  }

  NP lca(NP u, NP v) {
    if(not is_connected(u, v)) return nullptr;
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

  const Info &query(NP u) {
    expose(u);
    return get_info(u);
  }

  const Info &query_path(NP u, NP v) {
    evert(u);
    expose(v);
    return get_info(v);
  }

  Info query_subtree(NP u) {
    expose(u);
    NP l = u->l;
    u->l = nullptr;
    update(u);
    auto ret = u->info;
    u->l = l;
    update(u);
    return ret;
  }
};

/*
using T = int64_t;
// 遅延伝搬をするための作用素
struct Lazy {

  // 単位元
  Lazy() {}

  // 初期化
  Lazy(T v) {}

  // 遅延伝搬
  void propagate(const Lazy &p) {}
};

// Light-edge の情報
template< typename Lazy >
struct LInfo {

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() {}

  // 初期化
  LInfo(T v) {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {}

  // 部分木への遅延伝搬
  void propagate(const Lazy &p) {}
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
struct Info {

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() {}

  // 初期化
  Info(T v) {}

  // 反転
  void toggle() {}

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {}

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(); }

  // 遅延伝搬
  void propagate(const Lazy &p) {}

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
*/
