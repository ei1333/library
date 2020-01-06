#define IGNORE

template< typename T, typename Compare = less< T > >
struct PQ {
  priority_queue< T, vector< T >, Compare > que1, que2;
 
  PQ() = default;
 
  void push(T k) {
    que1.emplace(k);
  }
 
  void pop(T k) {
    que2.emplace(k);
  }
 
  inline void modify() {
    while(que2.size() && que2.top() == que1.top()) {
      que2.pop();
      que1.pop();
    }
  }
 
  bool empty() {
    modify();
    return que1.empty();
  }
 
  T top() {
    modify();
    return que1.top();
  }
};
 
int main() {
 
  struct Farthest {
    PQ< int64 > pq;
    int64 c_max, p_max, length;
 
    Farthest() : c_max(-infll), p_max(-infll), length(0) {}
 
    void merge(int64 key, const Farthest &parent, const Farthest &child) {
      p_max = max(child.p_max, child.length + key + max(pq.empty() ? 0 : pq.top(), parent.p_max));
      c_max = max(parent.c_max, parent.length + key + max(pq.empty() ? 0 : pq.top(), child.c_max));
      length = parent.length + key + child.length;
    }
 
    void toggle() {
      swap(c_max, p_max);
    }
 
    void add(const Farthest &child) {
      pq.push(child.c_max);
    }
 
    void erase(const Farthest &child) {
      pq.pop(child.c_max);
    }
  } e;
 
  int Q;
  cin >> Q;
 
  using LCT = LinkCutTreeSubtree< Farthest, int64 >;
  LCT lct(e);
  vector< LCT::Node * > ev(500001), ee(500001);
  ev[0] = lct.make_node(0);
 
  int num = 1;
  for(int i = 0; i < Q; i++) {
    int t, a, b;
    cin >> t >> a >> b;
    if(t == 1) {
      ev[num] = lct.make_node(0);
      ee[num] = lct.make_node(b);
      lct.link(ee[num], ev[a]);
      lct.link(ev[num], ee[num]);
      ++num;
    } else if(t == 2) {
      lct.set_key(ee[a], b);
    } else {
      lct.evert(ev[a]);
      cout << ev[a]->sum.c_max << "\n";
    }
  }
}
