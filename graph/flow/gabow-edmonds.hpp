// https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf

/**
 * @brief Gabow Edmonds(一般グラフの最大マッチング)
 * 
 */
struct GabowEdmonds {

  struct edge {
    int to, idx;
  };

  vector< vector< edge > > g;
  vector< pair< int, int > > edges;
  vector< int > mate, label, first;
  queue< int > que;

  GabowEdmonds(int n) : g(n + 1), mate(n + 1), label(n + 1, -1), first(n + 1) {}

  void add_edge(int u, int v) {
    ++u, ++v;
    g[u].push_back((edge) {v, (int) (edges.size() + g.size())});
    g[v].push_back((edge) {u, (int) (edges.size() + g.size())});
    edges.emplace_back(u, v);
  }

  int find(int x) {
    if(label[first[x]] < 0) return first[x];
    first[x] = find(first[x]);
    return first[x];
  }

  void rematch(int v, int w) {
    int t = mate[v];
    mate[v] = w;
    if(mate[t] != v) return;
    if(label[v] < (int)g.size()) {
      mate[t] = label[v];
      rematch(label[v], t);
    } else {
      int x = edges[label[v] - g.size()].first;
      int y = edges[label[v] - g.size()].second;
      rematch(x, y);
      rematch(y, x);
    }
  }

  void assign_label(int x, int y, int num) {
    int r = find(x);
    int s = find(y);
    int join = 0;
    if(r == s) return;
    label[r] = -num;
    label[s] = -num;
    while(true) {
      if(s != 0) swap(r, s);
      r = find(label[mate[r]]);
      if(label[r] == -num) {
        join = r;
        break;
      }
      label[r] = -num;
    }
    int v = first[x];
    while(v != join) {
      que.push(v);
      label[v] = num;
      first[v] = join;
      v = first[label[mate[v]]];
    }
    v = first[y];
    while(v != join) {
      que.push(v);
      label[v] = num;
      first[v] = join;
      v = first[label[mate[v]]];
    }
  }

  bool augment_check(int u) {
    que = queue< int >();
    first[u] = 0;
    label[u] = 0;
    que.push(u);
    while(!que.empty()) {
      int x = que.front();
      que.pop();
      for(auto e : g[x]) {
        int y = e.to;
        if(mate[y] == 0 && y != u) {
          mate[y] = x;
          rematch(x, y);
          return true;
        } else if(label[y] >= 0) {
          assign_label(x, y, e.idx);
        } else if(label[mate[y]] < 0) {
          label[mate[y]] = x;
          first[mate[y]] = y;
          que.push(mate[y]);
        }
      }
    }
    return false;
  }

  vector< pair< int, int > > max_matching() {
    for(int i = 1; i < (int)g.size(); i++) {
      if(mate[i] != 0) continue;
      if(augment_check(i)) label.assign(g.size(), -1);
    }
    vector< pair< int, int > > ret;
    for(int i = 1; i < (int)g.size(); i++) {
      if(i < mate[i]) ret.emplace_back(i - 1, mate[i] - 1);
    }
    return ret;
  }
};
