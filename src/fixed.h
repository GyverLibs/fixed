#pragma once
#include <stdint.h>

template <uint8_t bits>
constexpr int32_t _fixedMult(int32_t x, int32_t y) {
#ifdef FIXED_USE_64
    return (int64_t(x) * y) >> bits;
#else
    return bits >= 16 ? int32_t((int64_t(x) * y) >> bits) : ((x * y) >> bits);
#endif
}

template <uint8_t bits>
constexpr int32_t _fixedDiv(int32_t x, int32_t y) {
#ifdef FIXED_USE_64
    return (int64_t(x) * (int64_t(1) << bits)) / y;
#else
    return bits >= 16 ? int32_t((int64_t(x) * (int64_t(1) << bits)) / y) : ((x << bits) / y);
#endif
}

template <uint8_t f_bits>
class fixedT {
    static_assert(f_bits <= 30, "f_bits must be 0..30");

    constexpr fixedT(int32_t raw, bool) : raw(raw) {}

   public:
    static constexpr uint32_t SCALE = uint32_t(1) << f_bits;

    // ctr
    constexpr fixedT() : raw(0) {}
    constexpr fixedT(const fixedT& other) : raw(other.raw) {}

    template <typename T>
    constexpr fixedT(T val) : raw(int64_t(val) * SCALE) {}

    constexpr fixedT(float val) : raw(val * SCALE) {}
    constexpr fixedT(double val) : fixedT(float(val)) {}
    constexpr fixedT(long double val) : fixedT(float(val)) {}

    static constexpr fixedT fromRaw(int32_t raw) { return fixedT(raw, true); }

    // export
    constexpr int32_t getRaw() const { return raw; }
    constexpr int32_t toInt() const { return raw / int32_t(SCALE); }
    constexpr float toFloat() const { return float(raw) / SCALE; }

    // convert
    constexpr explicit operator bool() const { return raw; }
    constexpr operator char() const { return toInt(); }
    constexpr operator signed char() const { return toInt(); }
    constexpr operator unsigned char() const { return toInt(); }
    constexpr operator int() const { return toInt(); }
    constexpr operator unsigned int() const { return toInt(); }
    constexpr operator short() const { return toInt(); }
    constexpr operator unsigned short() const { return toInt(); }
    constexpr operator long() const { return toInt(); }
    constexpr operator unsigned long() const { return toInt(); }
    constexpr operator float() const { return toFloat(); }
    constexpr operator double() const { return toFloat(); }

    // math
    constexpr fixedT operator+(const fixedT& other) const { return fixedT(raw + other.raw, true); }
    constexpr fixedT operator-(const fixedT& other) const { return fixedT(raw - other.raw, true); }
    constexpr fixedT operator*(const fixedT& other) const { return fixedT(_fixedMult<f_bits>(raw, other.raw), true); }
    constexpr fixedT operator/(const fixedT& other) const { return other.raw ? fixedT(_fixedDiv<f_bits>(raw, other.raw), true) : fixedT(); }

    // math
    template <typename T>
    constexpr fixedT operator+(const T val) const { return *this + fixedT(val); }

    template <typename T>
    constexpr fixedT operator-(const T val) const { return *this - fixedT(val); }

    template <typename T>
    constexpr fixedT operator*(const T val) const { return fixedT(raw * val, true); }

    template <typename T>
    constexpr fixedT operator/(const T val) const { return val ? fixedT(raw / val, true) : fixedT(); }

    // template <typename T>
    // constexpr fixedT operator*(const T val) const { return *this * fixedT(val); }

    // template <typename T>
    // constexpr fixedT operator/(const T val) const { return *this / fixedT(val); }

    // math
    fixedT& operator+=(const fixedT& other) {
        raw += other.raw;
        return *this;
    }
    fixedT& operator-=(const fixedT& other) {
        raw -= other.raw;
        return *this;
    }
    fixedT& operator*=(const fixedT& other) {
        raw = _fixedMult<f_bits>(raw, other.raw);
        return *this;
    }
    fixedT& operator/=(const fixedT& other) {
        raw = other.raw ? _fixedDiv<f_bits>(raw, other.raw) : 0;
        return *this;
    }

    template <typename T>
    fixedT& operator*=(const T val) {
        raw *= val;
        return *this;
    }
    template <typename T>
    fixedT& operator/=(const T val) {
        raw = val ? raw / val : 0;
        return *this;
    }

    constexpr fixedT operator-() const {
        return fixedT(-raw, true);
    }

    // compare
    constexpr bool operator==(const fixedT& other) const { return raw == other.raw; }
    constexpr bool operator!=(const fixedT& other) const { return raw != other.raw; }
    constexpr bool operator<(const fixedT& other) const { return raw < other.raw; }
    constexpr bool operator<=(const fixedT& other) const { return raw <= other.raw; }
    constexpr bool operator>(const fixedT& other) const { return raw > other.raw; }
    constexpr bool operator>=(const fixedT& other) const { return raw >= other.raw; }

    template <typename T>
    constexpr bool operator==(const T val) const { return *this == fixedT(val); }
    template <typename T>
    constexpr bool operator!=(const T val) const { return *this != fixedT(val); }
    template <typename T>
    constexpr bool operator<(const T val) const { return *this < fixedT(val); }
    template <typename T>
    constexpr bool operator<=(const T val) const { return *this <= fixedT(val); }
    template <typename T>
    constexpr bool operator>(const T val) const { return *this > fixedT(val); }
    template <typename T>
    constexpr bool operator>=(const T val) const { return *this >= fixedT(val); }

    // static
    static constexpr int32_t MAX_INT = (int64_t(1) << (31 - f_bits)) - 1;
    static constexpr int32_t MIN_INT = -(int64_t(1) << (31 - f_bits));

    int32_t raw;
};

// operators T-f
template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator+(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) + rhs; }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator-(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) - rhs; }

// template <uint8_t f_bits, typename T>
// inline constexpr fixedT<f_bits> operator*(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) * rhs; }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator*(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>::fromRaw(lhs * rhs.raw); }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator/(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) / rhs; }

// compare T-f
template <uint8_t f_bits, typename T>
inline constexpr bool operator==(T lhs, const fixedT<f_bits>& rhs) { return rhs == lhs; }

template <uint8_t f_bits, typename T>
inline constexpr bool operator!=(T lhs, const fixedT<f_bits>& rhs) { return rhs != lhs; }

template <uint8_t f_bits, typename T>
inline constexpr bool operator<(T lhs, const fixedT<f_bits>& rhs) { return rhs > lhs; }

template <uint8_t f_bits, typename T>
inline constexpr bool operator<=(T lhs, const fixedT<f_bits>& rhs) { return rhs >= lhs; }

template <uint8_t f_bits, typename T>
inline constexpr bool operator>(T lhs, const fixedT<f_bits>& rhs) { return rhs < lhs; }

template <uint8_t f_bits, typename T>
inline constexpr bool operator>=(T lhs, const fixedT<f_bits>& rhs) { return rhs <= lhs; }

// fixed8
using fixed8 = fixedT<8>;
constexpr fixed8 operator"" _fx8(unsigned long long value) { return fixed8(value); }
constexpr fixed8 operator"" _fx8(long double value) { return fixed8(value); }

// fixed16
using fixed = fixedT<16>;  // legacy
using fixed16 = fixedT<16>;
constexpr fixed16 operator"" _fx16(unsigned long long value) { return fixed16(value); }
constexpr fixed16 operator"" _fx16(long double value) { return fixed16(value); }

// fixed24
using fixed24 = fixedT<24>;
constexpr fixed24 operator"" _fx24(unsigned long long value) { return fixed24(value); }
constexpr fixed24 operator"" _fx24(long double value) { return fixed24(value); }
