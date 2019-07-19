template< class D, class L, D (*f)(D, D), D (*g)(D, L), L (*h)(L, L), L (*p)(L, int) >
struct PersistentRedBlackTree : RedBlackTree< D, L, f, g, h, p > {
  using RBT = RedBlackTree< D, L, f, g, h, p >;
  using Node = typename RBT::Node;
 
  PersistentRedBlackTree(int sz, const D &M1, const L &OM0) :
      RBT(sz, M1, OM0) {}
 
  Node *clone(Node *t) override { return &(*RBT::pool.alloc() = *t); }
 
  Node *rebuild(Node *r) { return RBT::build(RBT::dump(r)); }
};
