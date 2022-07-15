#pragma once
#include <concepts>
#include <type_traits>
namespace RandNum {
inline int &precision() {
  static int precision = 5;
  return precision;
}

inline int &seed() {
  static int seed = 0;
  return seed;
}

namespace Detail {
inline uint64_t &sq_index() {
  static uint64_t sq_index = 0;
  return sq_index;
}

static uint64_t Squirrel3() {
  const uint64_t BIT_NOISE1 = 0xB5297A4DB5297A4D;
  const uint64_t BIT_NOISE2 = 0x68E31DA468E31DA4;
  const uint64_t BIT_NOISE3 = 0x1B56C4E91B56C4E9;
  auto position = sq_index()++;
  position *= BIT_NOISE1;
  position += seed();
  position ^= (position >> 8);
  position += BIT_NOISE2;
  position ^= (position << 8);
  position *= BIT_NOISE3;
  position ^= (position >> 8);
  return position;
};
} // namespace Detail

template <std::integral T> T getRandom() {
  return static_cast<T>(Detail::Squirrel3());
};
template <std::integral T> T getRandom(T high) {
  return getRandom<T>() % static_cast<uint64_t>(high);
};
template <std::integral T> T getRandom(T low, T high) {
  return static_cast<T>(low + getRandom(high - low));
};
template <std::floating_point T> T getRandom() {
  return static_cast<T>(Detail::Squirrel3());
};
template <std::floating_point T> T getRandom(T high) {
  T randFloat = getRandom<T>();
  for (auto i = 1; i < precision(); i++) {
    randFloat += getRandom<T>() / (T)pow(10, i);
  }
  return static_cast<T>(fmod(randFloat, high));
};
template <std::floating_point T> T getRandom(T low, T high) {
  return static_cast<T>(low + getRandom(high - low));
};
} // namespace RandNum