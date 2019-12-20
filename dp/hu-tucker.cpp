template< typename Heap, typename T >
T hu_tucker(vector< T > vs, T INF) {
  int N = (int) vs.size();
  Heap heap;
  vector< typename Heap::Node * > hs(N - 1, heap.makeheap());
  vector< int > ls(N), rs(N);
  vector< T > cs(N - 1);
  using pi = pair< T, int >;
  priority_queue< pi, vector< pi >, greater< pi > > que;
  for(int i = 0; i + 1 < N; i++) {
    ls[i] = i - 1;
    rs[i] = i + 1;
    cs[i] = vs[i] + vs[i + 1];
    que.emplace(cs[i], i);
  }
  T ret = 0;
  for(int k = 0; k + 1 < N; k++) {
    T c;
    int i;
    do {
      tie(c, i) = que.top();
      que.pop();
    } while(rs[i] < 0 || cs[i] != c);
 
    bool ml = false, mr = false;
    if(!heap.empty(hs[i]) && vs[i] + heap.top(hs[i]) == c) {
      heap.pop(hs[i]);
      ml = true;
    } else if(vs[i] + vs[rs[i]] == c) {
      ml = mr = true;
    } else {
      auto top = heap.pop(hs[i]);
      if(!heap.empty(hs[i]) && heap.top(hs[i]) + top == c) {
        heap.pop(hs[i]);
      } else {
        mr = true;
      }
    }
    ret += c;
    heap.push(hs[i], c);
    if(ml) vs[i] = INF;
    if(mr) vs[rs[i]] = INF;
 
    if(ml && i > 0) {
      int j = ls[i];
      hs[j] = heap.merge(hs[j], hs[i]);
      rs[j] = rs[i];
      rs[i] = -1;
      ls[rs[j]] = j;
      i = j;
    }
 
    if(mr && rs[i] + 1 < N) {
      int j = rs[i];
      hs[i] = heap.merge(hs[i], hs[j]);
      rs[i] = rs[j];
      rs[j] = -1;
      ls[rs[i]] = i;
    }
    cs[i] = vs[i] + vs[rs[i]];
 
    if(!heap.empty(hs[i])) {
      T top = heap.pop(hs[i]);
      cs[i] = min(cs[i], min(vs[i], vs[rs[i]]) + top);
      if(!heap.empty(hs[i])) cs[i] = min(cs[i], top + heap.top(hs[i]));
      heap.push(hs[i], top);
    }
    que.emplace(cs[i], i);
  }
  return ret;
}
