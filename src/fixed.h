#pragma once
#include <stdint.h>

#ifdef FIXED_USE_64
#define _FIX_MULT(x, y, bits) ((int64_t(x) * y) >> bits)
#define _FIX_DIV(x, y, bits) ((int64_t(x) << bits) / y)
#else
#define _FIX_MULT(x, y, bits) ((x * y) >> bits)
#define _FIX_DIV(x, y, bits) ((x << bits) / y)
#endif

template <uint8_t f_bits>
class fixedT {
    constexpr fixedT(int32_t raw, bool) : raw(raw) {}

   public:
    // ctr
    constexpr fixedT() : raw(0) {}
    constexpr fixedT(const fixedT& other) : raw(other.raw) {}

    template <typename T>
    constexpr fixedT(T val) : raw(int32_t(val) << f_bits) {}

    constexpr fixedT(float val) : raw(val * (1L << f_bits)) {}
    constexpr fixedT(double val) : fixedT(float(val)) {}
    constexpr fixedT(long double val) : fixedT(float(val)) {}

    // export
    constexpr int32_t getRaw() const { return raw; }
    constexpr int32_t toInt() const { return raw >> f_bits; }
    constexpr float toFloat() const { return float(raw) / (1L << f_bits); }

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
    constexpr fixedT operator*(const fixedT& other) const { return fixedT(_FIX_MULT(raw, other.raw, f_bits), true); }
    constexpr fixedT operator/(const fixedT& other) const { return fixedT(_FIX_DIV(raw, other.raw, f_bits), true); }

    // math
    template <typename T>
    constexpr fixedT operator+(const T val) const { return *this + fixedT(val); }

    template <typename T>
    constexpr fixedT operator-(const T val) const { return *this - fixedT(val); }

    template <typename T>
    constexpr fixedT operator*(const T val) const { return *this * fixedT(val); }

    template <typename T>
    constexpr fixedT operator/(const T val) const { return *this / fixedT(val); }

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
        raw = _FIX_MULT(raw, other.raw, f_bits);
        return *this;
    }
    fixedT& operator/=(const fixedT& other) {
        raw = _FIX_DIV(raw, other.raw, f_bits);
        return *this;
    }

    template <typename T>
    fixedT& operator*=(const T val) {
        raw *= val;
        return *this;
    }
    template <typename T>
    fixedT& operator/=(const T val) {
        raw /= val;
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
    static constexpr int32_t MAX_INT = (1L << (32 - f_bits - 1)) - 1;
    static constexpr int32_t MIN_INT = -(1L << (32 - f_bits - 1));

    int32_t raw;
};

// operators f-f
template <uint8_t f_bits>
inline constexpr fixedT<f_bits> operator+(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs.raw + rhs.raw, true); }

template <uint8_t f_bits>
inline constexpr fixedT<f_bits> operator-(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs.raw - rhs.raw, true); }

template <uint8_t f_bits>
inline constexpr fixedT<f_bits> operator*(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(_FIX_MULT(lhs.raw, rhs.raw, f_bits), true); }

template <uint8_t f_bits>
inline constexpr fixedT<f_bits> operator/(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(_FIX_DIV(lhs.raw, rhs.raw, f_bits), true); }

// operators T-f
template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator+(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) + rhs; }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator-(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) - rhs; }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator*(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) * rhs; }

template <uint8_t f_bits, typename T>
inline constexpr fixedT<f_bits> operator/(T lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>(lhs) / rhs; }

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