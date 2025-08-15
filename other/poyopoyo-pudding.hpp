/**
 *  🍮 PoyoPoyoPudding 🍮
 *
 *  - 最大 10 層までプリンを重ねられる。
 *  - 各層には「甘さ (0-100)」と「弾力 (0-100)」を保持。
 *  - addLayer でプルプルを追加、eatTop で一口たべる。
 *  - shake でランダムに弾力が変わる（ぷるん♪）。
 *  - operator<< で可視化。🍮
 */
struct PoyoPoyoPudding {
  struct Layer {
    uint8_t sweetness;    // 0-100
    uint8_t springiness;  // 0-100
  };

  static constexpr size_t kMaxLayers = 10;

  // ---- 状態 ---- //
  std::array<Layer, kMaxLayers> layers{};
  std::size_t top = 0;  // 現在の層数

  // ---- 挙動 ---- //
  bool addLayer(uint8_t sweet, uint8_t spring) {
    if (top == kMaxLayers) return false;
    layers[top++] = {sweet, spring};
    return true;
  }

  bool eatTop() {
    if (top == 0) return false;
    --top;
    return true;
  }

  void shake() {
    mt19937 rng{static_cast<uint32_t>(
        std::chrono::steady_clock::now().time_since_epoch().count())};
    std::uniform_int_distribution<int> dist(-5, +5);
    for (std::size_t i = 0; i < top; ++i) {
      int v = static_cast<int>(layers[i].springiness) + dist(rng);
      layers[i].springiness = static_cast<uint8_t>(std::clamp(v, 0, 100));
    }
  }

  // ---- デバッグ／鑑賞用 ---- //
  friend ostream& operator<<(ostream& os, const PoyoPoyoPudding& p) {
    os << "🍮 PoyoPoyoPudding (" << p.top << " / " << kMaxLayers
       << " layers)\n";
    for (size_t i = p.top; i-- > 0;) {
      const auto& L = p.layers[i];
      os << "  ├─ Layer " << setw(2) << i << " | Sweet " << setw(3)
         << int(L.sweetness) << " | Spring " << setw(3) << int(L.springiness)
         << '\n';
    }
    return os;
  }
};
