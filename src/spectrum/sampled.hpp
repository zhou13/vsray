#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

template<int n>
class SampledSpectrum {
protected:
    Float v[n];

public:
    SampledSpectrum() {
        std::fill_n(v, n, 0.f);
    }

    SampledSpectrum(Float f) {
        std::fill_n(v, n, f);
    }

    SampledSpectrum(Float f[]) {
        std::copy_n(f, n, v);
    }

    Float &operator[] (int index) {
        assert(0 <= index && index < n);
        return v[index];
    }

    SampledSpectrum operator+ (const SampledSpectrum &rhs) {
        SampledSpectrum r(v);
        for (int i = 0; i < n; ++i)
            r[i] += rhs[i];
        return r;
    }

    SampledSpectrum operator- (const SampledSpectrum &rhs) {
        SampledSpectrum r(v);
        for (int i = 0; i < n; ++i)
            r[i] -= rhs[i];
        return r;
    }

    SampledSpectrum operator* (const SampledSpectrum &rhs) {
        SampledSpectrum r(v);
        for (int i = 0; i < n; ++i)
            r[i] *= rhs[i];
        return r;
    }

    SampledSpectrum &operator+= (const SampledSpectrum &rhs) {
        for (int i = 0; i < n; ++i)
            v[i] += rhs[i];
        return *this;
    }

    SampledSpectrum &operator-= (const SampledSpectrum &rhs) {
        for (int i = 0; i < n; ++i)
            v[i] -= rhs[i];
        return *this;
    }

    SampledSpectrum &operator*= (const SampledSpectrum &rhs) {
        for (int i = 0; i < n; ++i)
            v[i] *= rhs[i];
        return *this;
    }

    SampledSpectrum operator* (const Float rhs) {
        SampledSpectrum r(v);
        for (int i = 0; i < n; ++i)
            r[i] *= rhs;
        return r;
    }

    SampledSpectrum operator/ (const Float rhs) {
        assert(rhs != 0);

        SampledSpectrum r(v);
        for (int i = 0; i < n; ++i)
            r[i] /= rhs;
        return r;
    }

    friend SampledSpectrum operator* (const Float f, const SampledSpectrum &s) {
        SampledSpectrum r(s.v);
        for (int i = 0; i < n; ++i)
            r[i] *= f;
        return r;
    }
};

VSRAY_NAMESPACE_END
