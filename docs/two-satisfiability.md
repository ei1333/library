## 概要

SAT(充足可能性問題) とは, いくつかの論理変数及びその否定からなる論理式が与えられたときに, 各変数に `true` または `false` を割り当てることによって論理式を `true` にできるかを判定する問題である.

次のような形の論理式を乗法標準形とよぶ.

$(a \lor b \lor \dots) \land (c \lor d \lor \dots) \land \dots$

$a, b, \cdots$ をリテラルと呼び, 論理変数かその否定が入る. $(a \lor b \lor \dots)$ のように $\land$ で繋がれた部分をクロージャと呼び, 全てのクロージャ内のリテラル数が高々 $2$ である乗法標準形の論理式に対する SAT を 2-SAT と呼ぶ.

クロージャ ($a \lor b)$ を $\Rightarrow$ (含意) を用いて $(\lnot a \Rightarrow b \land \lnot b \Rightarrow a)$ に変換する. すると乗法標準形は $(a \Rightarrow b) \land (c \Rightarrow d) \land \dots$ のようにすべて $\land$ で結ばれた論理式で表すことができる. ここで $x$ と $\lnot x$ に対応する頂点をつくって, $\Rightarrow$ を辺とした有向グラフを作成する。このグラフを強連結成分分解して $x$ と $\lnot x$ が同じ強連結成分に含まれるものが存在するとき充足不能, 逆に存在しないときは $x$ の強連結成分のトポロジカル順序が $\lnot x$ を含む強連結成分より後ろかどうかを真偽値として充足可能となる解を求めることが出来る.

## 使い方

* `TwoSatisfiability(N)`: `N` 個のリテラルで初期化する.
* `add_if(u, v)`: 条件 `u` ならば `v` を追加する.
* `add_or(u, v)`: 条件 `u` または `v` が `true` を追加する.
* `add_nand(u, v)`: 条件 `u` または `v` が `false` を追加する.
* `set_true(u)`: 条件 `u` が `true` を追加する.
* `set_false(u)`: 条件 `u` が `false` を追加する.
* `rev(u)`: 変数 `u` の否定を返す.
* `solve()`: 充足可能か判定し, 可能なら各変数の割り当ての例を格納した配列, 不能なら空配列を返す.

## 計算量

$O(V+E)$
