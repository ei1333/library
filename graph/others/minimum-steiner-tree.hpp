#include "../graph-template.hpp"

template <typename T>
struct MinimumSteinerTree {
  using pi = pair<int, int>;

  const T infty = numeric_limits<T>::max();

  vector<vector<T> > dp;
  T cost;

  MinimumSteinerTree() = default;

  explicit MinimumSteinerTree(const Graph<T>& g, const vector<int>& terminal)
      : g(g),
        terminal(terminal),
        dp(1 << terminal.size(), vector<T>(g.size(), infty)),
        pre(1 << terminal.size(), vector<pi>(g.size(), pi(-1, -1))) {
    assert(not terminal.empty());
    const int n = (int)g.size(), t = (int)terminal.size();
    for (int i = 0; i < t; i++) {
      assert(0 <= terminal[i] and terminal[i] < n);
      dp[1 << i][terminal[i]] = 0;
    }
    using qt = pair<T, int>;
    priority_queue<qt, vector<qt>, greater<> > que;
    for (int i = 1; i < (1 << t); i++) {
      for (int j = 0; j < n; j++) {
        for (int k = i; k > 0; k = (k - 1) & i) {
          if (dp[k][j] != infty and dp[i ^ k][j] != infty) {
            T nxt = dp[k][j] + dp[i ^ k][j];
            if (nxt < dp[i][j]) {
              dp[i][j] = nxt;
              pre[i][j] = {k, -1};
            }
          }
        }
      }
      for (int j = 0; j < n; j++) {
        if (dp[i][j] != infty) {
          que.emplace(dp[i][j], j);
        }
      }
      while (not que.empty()) {
        auto [now, v] = que.top();
        que.pop();
        if (dp[i][v] < now) continue;
        for (int j = 0; j < (int)g[v].size(); j++) {
          const auto& e = g[v][j];
          if (now + e.cost < dp[i][e.to]) {
            dp[i][e.to] = now + e.cost;
            pre[i][e.to] = {v, j};
            que.emplace(dp[i][e.to], e.to);
          }
        }
      }
    }
    cost = dp[(1 << t) - 1][terminal[0]];
  }

  Edges<T> restore() const {
    const int t = (int)terminal.size();
    assert(dp[(1 << t) - 1][terminal[0]] != infty);
    Edges<T> tree;
    vector<pair<int, int> > st;
    st.emplace_back((1 << t) - 1, terminal[0]);
    while (not st.empty()) {
      auto [x, y] = st.back();
      st.pop_back();
      if (pre[x][y].second == -1) {
        if (pre[x][y].first != -1) {
          st.emplace_back(pre[x][y].first, y);
          st.emplace_back(x ^ pre[x][y].first, y);
        }
      } else {
        tree.emplace_back(g[pre[x][y].first][pre[x][y].second]);
        st.emplace_back(x, pre[x][y].first);
      }
    }
    return tree;
  }

 private:
  const Graph<T>& g;
  const vector<int>& terminal;
  vector<vector<pi> > pre;
};
