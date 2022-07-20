#pragma once
#include <cmath>
#include <concepts>
#include <iostream>
#include <limits.h>
#include <type_traits>
namespace RandNum {
inline int &precision() {
  static int precision = 7;
  return precision;
}

inline int &seed() {
  static int seed = 0;
  return seed;
}

namespace Detail {
template <class T1, class T2> struct is_T : std::is_same<T1, T2> {};

template <class Tbase, class compType>
constexpr bool is_of_Ts(const compType type) {
  if (is_T<Tbase, compType>::value)
    return true;
  return false;
};
// accepts list of types as a basis for type concepts
template <class Tbase, class compType, class... Types>
constexpr bool is_of_Ts(const compType type, const Types... types) {
  if (is_T<Tbase, compType>::value)
    return true;
  return is_of_Ts<Tbase>(types...);
};
template <class T> constexpr bool isBoolean = is_T<T, bool>::value;

// note that for some reason, any type consisting of more than one word is not
// accepted by compilers, therefore a mix of both approaches is necessary
template <class T>
constexpr bool isInteger = is_of_Ts<T>(char(), wchar_t(), char8_t(), char16_t(),
                                       char32_t(), short(), int(), long()) ||
                           is_T<T, signed char>::value
                           || is_T<T, long long>::value
                           || is_T<T, signed char>::value
                           || is_T<T, unsigned int>::value
                           || is_T<T, unsigned char>::value
                           || is_T<T, unsigned long>::value
                           || is_T<T, unsigned short>::value
                           || is_T<T, unsigned long long>::value;
template <class T> constexpr bool isFloat = is_of_Ts<T>(float());
// another approach is typedeffing every type to a single word
typedef long double ldouble;
template <class T> constexpr bool isDouble = is_of_Ts<T>(double(), ldouble());

template <class T>
concept Boolean = isBoolean<T>;
template <class T>
concept Integral = isInteger<T>;
template <class T>
concept Float = isFloat<T>;
template <class T>
concept Double = isDouble<T>;

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

template <Detail::Integral T> T getRandom() {
  return static_cast<T>(Detail::Squirrel3());
};

template <Detail::Integral T> T getRandom(T high) {
  return getRandom<T>() % static_cast<uint64_t>(high);
};

template <Detail::Integral T> T getRandom(T low, T high) {
  return static_cast<T>(low + getRandom(high - low));
};

template <Detail::Float T> T getRandom() {
  return static_cast<T>(getRandom(static_cast<T>(8300000)));
};

template <Detail::Double T> T getRandom() {
  return static_cast<T>(getRandom(static_cast<T>(INT_MAX)));
};

template <std::floating_point T> T getRandom(T high) {
  T randFloat = getRandom<int>(static_cast<int>(high) + 1);
  if (precision() <= 9) {
    randFloat +=
        static_cast<T>(getRandom(0, static_cast<int>(powl(10, precision())))) /
        (T)pow(10.0, (T)precision());
  } else {
    for (auto i = 1; i < precision(); i++) {
      randFloat +=
          static_cast<T>(getRandom(10)) / static_cast<T>(pow(10.0, (T)i));
    }
  }
  return static_cast<T>(std::fmod(randFloat, high));
};

template <std::floating_point T> T getRandom(T low, T high) {
  return static_cast<T>(low + getRandom(high - low));
};

template <Detail::Boolean T> T getRandom() {
  return static_cast<T>(Detail::Squirrel3() % 2);
};

template <Detail::Boolean T> T getRandom(double high) {
  return getRandom<double>(static_cast<double>(1.0)) < high;
};
} // namespace RandNum