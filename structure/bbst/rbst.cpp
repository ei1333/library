template< typename T, typename F >
struct RBST : MergeSplitBasedBBST< T, F > {
private:
  using MergeSplitBasedBBST< T, F >::MergeSplitBasedBBST;
  using NP = typename MergeSplitBasedBBST< T, F >::NP;
  using MergeSplitBasedBBST< T, F >::count;
  using MergeSplitBasedBBST< T, F >::update;

  int xor128() {
    static int x = 123456789;
    static int y = 362436069;
    static int z = 521288629;
    static int w = 88675123;
    int t;

    t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }

  NP imp_merge(NP l, NP r) override {
    if(!l || !r) return l ? l : r;
    if(xor128() % (count(l) + count(r)) < count(l)) {
      l->ch[1] = imp_merge(l->ch[1], r);
      return update(l);
    } else {
      r->ch[0] = imp_merge(l, r->ch[0]);
      return update(r);
    }
  }

  pair< NP, NP > imp_split(NP t, int k) override {
    if(!t) return {t, t};
    if(k <= count(t->ch[0])) {
      auto s = imp_split(t->ch[0], k);
      t->ch[0] = s.second;
      return {s.first, update(t)};
    } else {
      auto s = imp_split(t->ch[1], k - count(t->ch[0]) - 1);
      t->ch[1] = s.first;
      return {update(t), s.second};
    }
  }

public:
  void set_element(NP &t, int k, const T &x) {
    if(k < count(t->ch[0])) set_element(t->ch[0], k, x);
    else if(k == count(t->ch[0])) t->key = t->sum = x;
    else set_element(t->ch[1], k - count(t->ch[0]) - 1, x);
    t = update(t);
  }
};
