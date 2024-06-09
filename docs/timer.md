---
title: Timer
documentation_of: //other/timer.hpp
---

rdtsc (Read Time Stamp Counter) 命令を用いると CPU クロックごとに加算される 64 bit のタイムスタンプカウンタの値を得ることができる. マラソンするときにタイマーとしてよく用いられるらしい.

CPUのクロック周波数がわかれば, カウンタの値から実行時間を推定することができる. 参考までにAtCoder では 2.90GHz, Codeforces では 3.60GHz, yukicoder では 2.3GHz (2024/06/09現在).

## ベンチマーク

$10^8$ 回呼び出したときの実行時間の比較. 間違っていたらごめんなさい.

AtCoder:

- `clock()`: inf
- `chrono::high_resolution_clock::now()`: 2150 ms
- `rdtsc`: 750 ms

Codeforces:

- `clock()`: 870 ms 
- `chrono::high_resolution_clock::now()`: 1660 ms
- `rdtsc`: 700 ms

yukicoder:

- `clock()`: inf 
- `chrono::high_resolution_clock::now()`: 3330 ms
- `rdtsc`: 1020 ms

# コンストラクタ

```cpp
Timer()
```

# reset

```cpp
void reset()
```

タイマーを初期化します。

# get_second

```cpp
inline double get_second() const
```

経過時間を秒数で返します。

# get_cycle

```cpp
inline uint64_t get_cycle() const
```

経過時間をクロック数で返します。
