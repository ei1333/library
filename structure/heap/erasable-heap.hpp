#pragma once

#include <cassert>
#include <queue>

template < typename T, class Container = std::vector< T >, class Compare = std::less< typename Container::value_type > > 
class erasable_heap {
  std::priority_queue< T, Container, Compare > base, erased;

  void normalize() {
    while (true) {
      if (base.empty()) break;
      if (erased.empty()) break;
      if (base.top() != erased.top()) break;
      base.pop();
      erased.pop();
    }
  }

  public:
  bool empty() const { return base.empty(); }

  const T &top() const {
    assert( !empty() );
    return base.top();
  }

  void push(T val) {
    base.push(std::move(val));
    normalize();
  }

  template < class... Args >
    void emplace(Args... args) {
      base.emplace(args...);
      normalize();
    }

  void pop() {
    assert( !empty() );
    base.pop();
    normalize();
  }

  void erase(T val) {
    erased.push(std::move(val));
    normalize();
  }
};
