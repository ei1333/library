template< typename SemiGroup >
struct SlidingWindowAggregation {
  using F = function< SemiGroup(SemiGroup, SemiGroup) >;
 
  struct Node {
    SemiGroup val, sum;
 
    Node(const SemiGroup &val, const SemiGroup &sum) : val(val), sum(sum) {}
  };
 
  SlidingWindowAggregation(F f) : f(f) {}
 
 
  const F f;
  stack< Node > front, back;
 
  bool empty() const {
    return front.empty() && back.empty();
  }
 
  size_t size() const {
    return front.size() + back.size();
  }
 
  SemiGroup fold_all() const {
    if(front.empty()) {
      return back.top().sum;
    } else if(back.empty()) {
      return front.top().sum;
    } else {
      return f(front.top().sum, back.top().sum);
    }
  }
 
  void push(const SemiGroup &x) {
    if(back.empty()) {
      back.emplace(x, x);
    } else {
      back.emplace(x, f(back.top().sum, x));
    }
  }
 
  void pop() {
    if(front.empty()) {
      front.emplace(back.top().val, back.top().val);
      back.pop();
      while(!back.empty()) {
        front.emplace(back.top().val, f(back.top().val, front.top().sum));
        back.pop();
      }
    }
    front.pop();
  }
};
