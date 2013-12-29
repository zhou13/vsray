#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class RGBSpectrum {
private:
    real v[3];

public:
    RGBSpectrum() {
        v[0] = v[1] = v[2] = 0.f;
    }

    RGBSpectrum(real f) {
        std::fill_n(v, 3, f);
    }

    RGBSpectrum(real r, real g, real b) {
        v[0] = r;
        v[1] = g;
        v[2] = b;
    }

    RGBSpectrum(const real *f) {
        std::copy_n(f, 3, v);
    }

    real &operator[](int index) {
        assert(0 <= index && index < 3);
        return v[index];
    }

    real operator[](int index) const {
        assert(0 <= index && index < 3);
        return v[index];
    }

    void getRGB(real rgb[3]) {
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

    RGBSpectrum operator*(const real rhs) {
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] *= rhs;
        return r;
    }

    RGBSpectrum operator/(const real rhs) {
        assert(rhs != 0);

        real inv = 1.f / rhs;
        RGBSpectrum r(v);
        for (int i = 0; i < 3; ++i)
            r[i] *= inv;
        return r;
    }

    RGBSpectrum &operator+=(const real rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] += rhs;
        return *this;
    }

    RGBSpectrum &operator-=(const real rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] -= rhs;
        return *this;
    }

    RGBSpectrum &operator*=(const real rhs) {
        for (int i = 0; i < 3; ++i)
            v[i] *= rhs;
        return *this;
    }

    RGBSpectrum &operator/=(const real rhs) {
        assert(rhs != 0);

        real inv = 1.f / rhs;
        for (int i = 0; i < 3; ++i)
            v[i] *= inv;
        return *this;
    }

    friend RGBSpectrum operator*(const real f, const RGBSpectrum &s) {
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
