template< typename SUM, typename KEY >
struct LinkCutTreeSubtree {
 
  struct Node {
    Node *l, *r, *p;
 
    KEY key;
    SUM sum;
 
    bool rev;
    int sz;
 
    bool is_root() const {
      return !p || (p->l != this && p->r != this);
    }
 
    Node(const KEY &key, const SUM &sum) :
        key(key), sum(sum), rev(false), sz(1),
        l(nullptr), r(nullptr), p(nullptr) {}
  };
 
  const SUM ident;
 
  LinkCutTreeSubtree(const SUM &ident) : ident(ident) {}
 
  Node *make_node(const KEY &key) {
    auto ret = new Node(key, ident);
    update(ret);
    return ret;
  }
 
  Node *set_key(Node *t, const KEY &key) {
    expose(t);
    t->key = key;
    update(t);
    return t;
  }
 
  void toggle(Node *t) {
    swap(t->l, t->r);
    t->sum.toggle();
    t->rev ^= true;
  }
 
  void push(Node *t) {
    if(t->rev) {
      if(t->l) toggle(t->l);
      if(t->r) toggle(t->r);
      t->rev = false;
    }
  }
 
 
  void update(Node *t) {
    t->sz = 1;
    if(t->l) t->sz += t->l->sz;
    if(t->r) t->sz += t->r->sz;
    t->sum.merge(t->key, t->l ? t->l->sum : ident, t->r ? t->r->sum : ident);
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
    for(auto *cur = t; cur; cur = cur->p) {
      splay(cur);
      if(cur->r) cur->sum.add(cur->r->sum);
      cur->r = rp;
      if(cur->r) cur->sum.erase(cur->r->sum);
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
 
  SUM &query(Node *t) {
    expose(t);
    return t->sum;
  }
};
