struct ConnectedGridStates {
 private:
  vector<vector<vector<int> > > states;
  vector<vector<int> > nxt_wall, nxt_ground;
  int width;

 public:
  explicit ConnectedGridStates(int width)
      : width(width), states(width), nxt_wall(width), nxt_ground(width) {
    assert(width > 0);

    auto modify = [&](vector<int> B) {
      vector<int> id(width, -1);
      int now = 0;
      for (int i = 0; i < width; i++) {
        if (B[i] != -1) {
          if (id[B[i]] == -1) {
            id[B[i]] = now++;
          }
          B[i] = id[B[i]];
        }
      }
      return B;
    };

    vector<map<vector<int>, int> > ids(width);
    queue<pair<int, int> > que;  // {col, state_id}

    {
      vector<int> state(width, -1);
      states[0].emplace_back(state);
      ids[0].emplace(state, 0);
      nxt_wall[0].emplace_back(-1);
      nxt_ground[0].emplace_back(-1);
      que.emplace(0, 0);
    }

    auto push = [&](int nxt, const vector<int> &state) -> int {
      auto it = ids[nxt].emplace(state, states[nxt].size());
      if (it.second) {
        states[nxt].emplace_back(state);
        nxt_wall[nxt].emplace_back(-1);
        nxt_ground[nxt].emplace_back(-1);
        que.emplace(nxt, it.first->second);
      }
      return it.first->second;
    };

    while (not que.empty()) {
      auto [i, id] = que.front();
      que.pop();
      int j = i + 1 == width ? 0 : i + 1;
      auto &state = states[i][id];
      int mx = *max_element(state.begin(), state.end());
      {  // '.'
        if (state[i] == -1) {
          nxt_ground[i][id] = push(j, state);
        } else {
          bool ok = false;
          for (int k = 0; k < width; k++) {
            ok |= i != k and state[k] == state[i];
          }
          if (ok) {
            auto to = state;
            to[i] = -1;
            nxt_ground[i][id] = push(j, modify(to));
          } else if (mx >= 1) {  // disconnected
            nxt_ground[i][id] = -1;
          } else {  // disappeared
            nxt_ground[i][id] = -2;
          }
        }
      }
      {  // '#'
        auto to = state;
        if (i == 0) {
          if (state[i] == -1) {
            to[i] = mx + 1;
          }
        } else {
          if (state[i] == -1) {
            if (state[i - 1] == -1) {
              to[i] = mx + 1;
            } else {
              to[i] = state[i - 1];
            }
          } else if (state[i - 1] != -1) {
            for (int k = 0; k < width; k++) {
              if (state[k] == state[i]) {
                to[k] = state[i - 1];
              }
            }
          }
        }
        nxt_wall[i][id] = push(j, modify(to));
      }
    }
    for (int i = 0; i < width; i++) {
      int j = i + 1 == width ? 0 : i + 1;
      int sz = (int)states[j].size();
      for (auto &k : nxt_ground[i]) {
        if (k == -2) k = sz;
      }
      for (auto &k : nxt_wall[i]) {
        if (k == -2) k = sz;
      }
      nxt_ground[i].emplace_back(sz);
      nxt_wall[i].emplace_back(-1);
    }
    for (int i = 0; i < width; i++) {
      states[i].emplace_back(width, -1);
    }
  }

  inline int set_wall(int k, int state) const { return nxt_wall[k][state]; }

  inline int set_ground(int k, int state) const { return nxt_ground[k][state]; }

  inline const vector<vector<int> > &operator[](int k) const {
    return states[k >= width ? k - width : k];
  }
};
