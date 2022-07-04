struct Dice
{
  // int x, y;
  int l, r, f, b, d, u;

  void RollN()
  {
    //  --y;
    int buff = d;
    d = f;
    f = u;
    u = b;
    b = buff;
  }

  void RollS()
  {
    // ++y;
    int buff = d;
    d = b;
    b = u;
    u = f;
    f = buff;
  }

  void RollL() // ----->
  {
    int buff = f;
    f = l;
    l = b;
    b = r;
    r = buff;
  }

  void RollR() // <------
  {
    int buff = f;
    f = r;
    r = b;
    b = l;
    l = buff;
  }

  void RollE() // .o -> o.
  {
    // --x;
    int buff = d;
    d = l;
    l = u;
    u = r;
    r = buff;
  }


  void RollW() // o. -> .o
  {
    //  ++x;
    int buff = d;
    d = r;
    r = u;
    u = l;
    l = buff;
  }


  vector< Dice > makeDice()
  {
    vector< Dice > ret;
    for(int i = 0; i < 6; i++) {
      Dice d(*this);
      if(i == 1) d.RollN();
      if(i == 2) d.RollS();
      if(i == 3) d.RollS(), d.RollS();
      if(i == 4) d.RollL();
      if(i == 5) d.RollR();
      for(int j = 0; j < 4; j++) {
        ret.emplace_back(d);
        d.RollE();
      }
    }
    return (ret);
  }
};
