template< typename Monoid, typename OperatorMonoid, typename F, typename G, typename H, size_t FULL = 1000 >
struct PersistentLazyRedBlackTree : LazyRedBlackTree< Monoid, OperatorMonoid, F, G, H > {
  using RBT = LazyRedBlackTree< Monoid, OperatorMonoid, F, G, H >;
  using RBT::LazyRedBlackTree;
  using Node = typename RBT::Node;
 
private:
  Node *clone(Node *t) override {
    return &(*RBT::pool.alloc() = *t);
  }
 
public:
  Node *rebuild(Node *r) {
    auto ret = RBT::dump(r);
    RBT::pool.clear();
    return RBT::build(ret);
  }
 
  bool almost_full() const {
    return this->pool.ptr < FULL;
  }
};
