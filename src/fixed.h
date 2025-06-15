#pragma once
#include <stdint.h>

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
    constexpr explicit operator char() const { return toInt(); }
    constexpr explicit operator signed char() const { return toInt(); }
    constexpr explicit operator unsigned char() const { return toInt(); }
    constexpr explicit operator int() const { return toInt(); }
    constexpr explicit operator unsigned int() const { return toInt(); }
    constexpr explicit operator short() const { return toInt(); }
    constexpr explicit operator unsigned short() const { return toInt(); }
    constexpr explicit operator long() const { return toInt(); }
    constexpr explicit operator unsigned long() const { return toInt(); }
    constexpr explicit operator long long() const { return toInt(); }
    constexpr explicit operator unsigned long long() const { return toInt(); }
    constexpr explicit operator float() const { return toFloat(); }
    constexpr explicit operator double() const { return toFloat(); }

    // math
    constexpr fixedT operator+(const fixedT& other) const { return fixedT(raw + other.raw, true); }
    constexpr fixedT operator-(const fixedT& other) const { return fixedT(raw - other.raw, true); }
    constexpr fixedT operator*(const fixedT& other) const { return fixedT((int64_t(raw) * other.raw) >> f_bits, true); }
    constexpr fixedT operator/(const fixedT& other) const { return fixedT((int64_t(raw) << f_bits) / other.raw, true); }

    fixedT& operator+=(const fixedT& other) {
        raw += other.raw;
        return *this;
    }
    fixedT& operator-=(const fixedT& other) {
        raw -= other.raw;
        return *this;
    }
    fixedT& operator*=(const fixedT& other) {
        raw = (int64_t(raw) * other.raw) >> f_bits;
        return *this;
    }
    fixedT& operator/=(const fixedT& other) {
        raw = (int64_t(raw) << f_bits) / other.raw;
        return *this;
    }

    template <typename T>
    fixedT& operator*=(const T& val) {
        raw *= val;
        return *this;
    }
    template <typename T>
    fixedT& operator/=(const T& val) {
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
inline constexpr fixedT<f_bits> operator*(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>((int64_t(lhs.raw) * rhs.raw) >> f_bits, true); }

template <uint8_t f_bits>
inline constexpr fixedT<f_bits> operator/(const fixedT<f_bits>& lhs, const fixedT<f_bits>& rhs) { return fixedT<f_bits>((int64_t(lhs.raw) << f_bits) / rhs.raw, true); }

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