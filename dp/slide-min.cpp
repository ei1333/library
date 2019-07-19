template< typename T >
vector< T > slide_min(const vector< T > &v, int k)
{
  deque< int > deq;
  vector< T > ret;
  for(int i = 0; i < v.size(); i++) {
    while(!deq.empty() && v[deq.back()] >= v[i]) {
      deq.pop_back();
    }
    deq.push_back(i);
    if(i - k + 1 >= 0) {
      ret.emplace_back(v[deq.front()]);
      if(deq.front() == i - k + 1) deq.pop_front();
    }
  }
  return ret;
}
