/**
 * @brief Persistent-Weight-Balanced-Tree(永続重み平衡木)
 */
template< typename Monoid, typename F, size_t FULL = 1000 >
struct PersistentWeightBalancedTree : WeightBalancedTree< Monoid, F > {
  using WBT = WeightBalancedTree< Monoid, F >;
  using WBT::WeightBalancedTree;
  using Node = typename WBT::Node;

private:
  Node *clone(Node *t) override {
    return &(*WBT::pool.alloc() = *t);
  }

public:
  Node *rebuild(Node *r) {
    auto ret = WBT::dump(r);
    WBT::pool.clear();
    return WBT::build(ret);
  }

  bool almost_full() const {
    return this->pool.ptr < FULL;
  }
};
