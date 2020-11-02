template< typename T >
struct Diameter {

  using key_t = pair< bool, T >;
  static const T inf = numeric_limits< T >::max() / 3;

  struct light_t {
    T val, dia;

    T top1, top2;
    T diameter;

    light_t() : top1(-inf), top2(-inf), diameter(-inf) {}

    void set_sum() {
      top1 = val;
      top2 = -inf;
      diameter = dia;
    }

    void update(const light_t &p) {
      if(top1 < p.top1) {
        top2 = top1;
        top1 = p.top1;
        if(top2 < p.top2) {
          top2 = p.top2;
        }
      } else if(top2 < p.top1) {
        top2 = p.top1;
      }
      if(diameter < p.diameter) {
        diameter = p.diameter;
      }
    }
  };

  struct heavy_t {
    bool vertex;
    T key;

    T all, p_len, c_len, diameter;

    heavy_t() : all(0), p_len(-inf), c_len(-inf), diameter(-inf) {}

    void set_key(const key_t &x) {
      vertex = x.first;
      key = x.second;
    }

    void update(const heavy_t &p, const heavy_t &c, const light_t &l) {
      if(vertex) {
        all = p.all + c.all;
        p_len = max({c.p_len, max(l.top1, p.p_len) + c.all, -inf});
        c_len = max({p.c_len, max(l.top1, c.c_len) + p.all, -inf});
        diameter = max({p.diameter, c.diameter, p.p_len + max(l.top1, c.c_len), c.c_len + l.top1, l.top1 + l.top2, l.diameter, -inf});
        if(key) {
          p_len = max(p_len, c.all);
          c_len = max(c_len, p.all);
          diameter = max({diameter, p.p_len, c.c_len, l.top1, T(0)});
        }
      } else {
        all = p.all + c.all + key;
        p_len = max({c.p_len, max(l.top1, p.p_len) + key + c.all, -inf});
        c_len = max({p.c_len, max(l.top1, c.c_len) + key + p.all, -inf});
        diameter = max({p.diameter, c.diameter, p.p_len + max(l.top1, c.c_len) + key, c.c_len + l.top1 + key, l.top1 + l.top2 + key, l.diameter, -inf});
      }
    }

    light_t add() const {
      light_t x;
      x.val = c_len;
      x.dia = diameter;
      return x;
    }
  };
};
