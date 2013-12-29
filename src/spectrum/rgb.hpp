#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class RGBSpectrum {
private:
    Float v[3];

public:
    RGBSpectrum() {
        v[0] = v[1] = v[2] = 0.f;
    }

    RGBSpectrum(Float f) {
        std::fill_n(v, 3, f);
    }

    RGBSpectrum(Float r, Float g, Float b) {
        v[0] = r;
        v[1] = g;
        v[2] = b;
    }

    RGBSpectrum(const Float *f) {
        std::copy_n(f, 3, v);
    }

    Float &operator[](int index) {
        assert(0 <= index && index < 3);
        return v[index];
    }

    Float operator[](int index) const {
        assert(0 <= index && index < 3);
        return v[index];
    }

    void getRGB(Float rgb[3]) {
        rgb[0] = v[0];
        rgb[1] = v[1];
        rgb[2] = v[2];
    }

    RGBSpectrum operator+(const RGBSpectrum &rhs) {
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] += rhs[i];
        return r;
    }

    RGBSpectrum operator-(const RGBSpectrum &rhs) {
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] -= rhs[i];
        return r;
    }

    RGBSpectrum operator*(const RGBSpectrum &rhs) {
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] *= rhs[i];
        return r;
    }

    RGBSpectrum &operator+=(const RGBSpectrum &rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] += rhs[i];
        return *this;
    }

    RGBSpectrum &operator-=(const RGBSpectrum &rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] -= rhs[i];
        return *this;
    }

    RGBSpectrum &operator*=(const RGBSpectrum &rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] *= rhs[i];
        return *this;
    }

    RGBSpectrum operator*(const Float rhs) {
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] *= rhs;
        return r;
    }

    RGBSpectrum operator/(const Float rhs) {
        assert(rhs != 0);

        Float inv = 1.f / rhs;
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] *= inv;
        return r;
    }

    RGBSpectrum &operator+=(const Float rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] += rhs;
        return *this;
    }

    RGBSpectrum &operator-=(const Float rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] -= rhs;
        return *this;
    }

    RGBSpectrum &operator*=(const Float rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] *= rhs;
        return *this;
    }

    RGBSpectrum &operator/=(const Float rhs) {
        assert(rhs != 0);

        Float inv = 1.f / rhs;
        for (int i = 0; i < 3; ++i)
            v[i] *= inv;
        return *this;
    }

    friend RGBSpectrum operator*(const Float f, const RGBSpectrum &s) {
        RGBSpectrum r(s.v);
        for (int i = 0; i < 3; ++i)
            r[i] *= f;
        return r;
    }

    string toString() {
        return "( " +
            lexical_cast<string>(v[0]) + " " +
            lexical_cast<string>(v[1]) + " " +
            lexical_cast<string>(v[2]) + " )";
    }
};

VSRAY_NAMESPACE_END
