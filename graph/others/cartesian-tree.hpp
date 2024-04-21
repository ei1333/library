#pragma once
/**
 * @brief Cartesian Tree
 * 
 * @see https://kimiyuki.net/blog/2020/07/27/recursion-on-cartesian-tree/
 */
template< typename T >
vector< int > cartesian_tree(const vector< T > &v) {
  int n = (int) v.size();
  vector< int > par(n, -1);
  stack< int > st;
  for(int i = 0; i < n; i++) {
    int last = -1;
    while(!st.empty() && v[st.top()] >= v[i]) {
      last = st.top();
      st.pop();
    }
    if(!st.empty()) par[i] = st.top();
    if(last >= 0) par[last] = i;
    st.emplace(i);
  }
  return par;
}
