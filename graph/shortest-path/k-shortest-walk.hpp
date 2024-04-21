#pragma once

#include "../graph-template.hpp"

/**
 * @brief K-Shortest-Walk
 * 
 * @see https://qiita.com/hotman78/items/42534a01c4bd05ed5e1e
 */
template< typename T >
vector< T > k_shortest_walk(const Graph< T > &g, int s, int t, int k) {
  int N = (int) g.size();
  Graph< T > rg(N);
  for(int i = 0; i < N; i++) {
    for(auto &e : g[i]) rg.add_directed_edge(e.to, i, e.cost);
  }
  auto dist = dijkstra(rg, t);
  if(dist.from[s] == -1) return {};
  auto &p = dist.dist;
  vector< vector< int > > ch(N);
  for(int i = 0; i < N; i++) {
    if(dist.from[i] >= 0) ch[dist.from[i]].emplace_back(i);
  }
  using PHeap = PersistentLeftistHeap< T >;
  using Node = typename PHeap::Node;
  PHeap heap;
  vector< Node * > h(N, heap.make_root());
  {
    queue< int > que;
    que.emplace(t);
    while(!que.empty()) {
      int idx = que.front();
      que.pop();
      if(dist.from[idx] >= 0) {
        h[idx] = heap.meld(h[idx], h[dist.from[idx]]);
      }
      bool used = true;
      for(auto &e : g[idx]) {
        if(e.to != t && dist.from[e.to] == -1) continue;
        if(used && dist.from[idx] == e.to && p[e.to] + e.cost == p[idx]) {
          used = false;
          continue;
        }
        h[idx] = heap.push(h[idx], e.cost - p[idx] + p[e.to], e.to);
      }
      for(auto &to : ch[idx]) que.emplace(to);
    }
  }
  using pi = pair< T, Node * >;
  auto comp = [](const pi &x, const pi &y) { return x.first > y.first; };
  priority_queue< pi, vector< pi >, decltype(comp) > que(comp);
  Node *root = heap.make_root();
  root = heap.push(root, p[s], s);
  que.emplace(p[s], root);
  vector< T > ans;
  while(!que.empty()) {
    T cost;
    Node *cur;
    tie(cost, cur) = que.top();
    que.pop();
    ans.emplace_back(cost);
    if((int)ans.size() == k) break;
    if(cur->l) que.emplace(cost + cur->l->key - cur->key, cur->l);
    if(cur->r) que.emplace(cost + cur->r->key - cur->key, cur->r);
    if(h[cur->idx]) que.emplace(cost + h[cur->idx]->key, h[cur->idx]);
  }
  return ans;
}
