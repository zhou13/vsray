#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class Matrix4x1 {
public:
    union {
        Float m[4];
        Float v[4];
    };
    Matrix4x1() {
        m[0] = m[1] = m[2] = m[3] = 0;
    }
    explicit Matrix4x1(const Vector &v) {
        m[0] = v.x;
        m[1] = v.y;
        m[2] = v.z;
        m[3] = 0.f;
    }
    explicit Matrix4x1(const Point &v) {
        m[0] = v.x;
        m[1] = v.y;
        m[2] = v.z;
        m[3] = 1.f;
    }
    explicit Matrix4x1(const Normal &v) {
        m[0] = v.x;
        m[1] = v.y;
        m[2] = v.z;
        m[3] = 1.f;
    }
    explicit Matrix4x1(Float *m_) {
        m[0] = m_[0];
        m[1] = m_[1];
        m[2] = m_[2];
        m[3] = m_[3];
    }
    explicit operator Vector() {
        return Vector(m[0], m[1], m[2]);
    }
    explicit operator Point() {
        if (m[3] == 1)
            return Point(m[0], m[1], m[2]);
        else {
            assert(m[3] != 0);
            return Point(m[0]/m[3], m[1]/m[3], m[2]/m[3]);
        }
    }
    explicit operator Normal() {
        return Normal(m[0], m[1], m[2]);
    }
    Matrix4x1(Float m0, Float m1, Float m2, Float m3) {
        m[0] = m0;
        m[1] = m1;
        m[2] = m2;
        m[3] = m3;
    }
    string toString() {
        return (lexical_cast<string>(m[0]) + " " +
                lexical_cast<string>(m[1]) + " " +
                lexical_cast<string>(m[2]) + " " +
                lexical_cast<string>(m[3]));
    }
    Matrix4x1 operator +(const Matrix4x1 &rhs) {
        Matrix4x1 r;
        for (int i = 0; i < 4; ++i)
            r.m[i] = m[i] + rhs.m[i];
        return r;
    }
    Matrix4x1 operator -(const Matrix4x1 &rhs) {
        Matrix4x1 r;
        for (int i = 0; i < 4; ++i)
            r.m[i] = m[i] - rhs.m[i];
        return r;
    }
    Matrix4x1 operator *(const Float &rhs) {
        Matrix4x1 r;
        for (int i = 0; i < 4; ++i)
            r.m[i] = m[i] * rhs;
        return r;
    }
    Matrix4x1 operator /(const Float &rhs) {
        assert(rhs != 0);

        Matrix4x1 r;
        Float t = 1.f / rhs;
        for (int i = 0; i < 4; ++i)
            r.m[i] = m[i] / t;
        return r;
    }
};

class Matrix4x4 {
public:
    union {
        Float v[4][4];
        Float m[16];
    };

    Matrix4x4() {
        memset(v, 0, sizeof(v));
    }

    Matrix4x4(Float diag) {
        memset(v, 0, sizeof(v));
        v[0][0] = v[1][1] = v[2][2] = v[3][3] = diag;
    }

    Matrix4x4(Float *m_) {
        memmove(m, m_, sizeof(m));
    }

    Matrix4x4(Float m0, Float m1, Float m2, Float m3,
              Float m4, Float m5, Float m6, Float m7,
              Float m8, Float m9, Float m10, Float m11,
              Float m12, Float m13, Float m14, Float m15)
    {
        m[0 ] = m0 ; m[1 ] = m1 ; m[2 ] = m2 ; m[3 ] = m3 ;
        m[4 ] = m4 ; m[5 ] = m5 ; m[6 ] = m6 ; m[7 ] = m7 ;
        m[8 ] = m8 ; m[9 ] = m9 ; m[10] = m10; m[11] = m11;
        m[12] = m12; m[13] = m13; m[14] = m14; m[15] = m15;
    }

    string toString() const {
        string r;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (j)
                    r += ' ';
                r += lexical_cast<string>(v[i][j]);
            }
            r += '\n';
        }
        return r;
    }

    Matrix4x4 operator +(const Matrix4x4 &rhs) const {
        Matrix4x4 r;
        for (int i = 0; i < 16; ++i)
            r.m[i] = m[i] + rhs.m[i];
        return r;
    }

    Matrix4x4 operator -(const Matrix4x4 &rhs) const {
        Matrix4x4 r;
        for (int i = 0; i < 16; ++i)
            r.m[i] = m[i] - rhs.m[i];
        return r;
    }

    Matrix4x4 operator *(const Matrix4x4 &rhs) const {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int k = 0; k < 4; ++k)
                for (int j = 0; j < 4; ++j)
                    r.v[i][j] += v[i][k] * rhs.v[k][j];
        return r;
    }

    Matrix4x1 operator *(const Matrix4x1 &rhs) const {
        Matrix4x1 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.v[i] += v[i][j] * rhs.v[j];
        return r;
    }

    Matrix4x4 operator *(const Float &rhs) const {
        Matrix4x4 r;
        for (int i = 0; i < 16; ++i)
            r.m[i] = m[i] * rhs;
        return r;
    }

    Matrix4x4 operator /(const Float &rhs) const {
        assert(rhs != 0);

        Matrix4x4 r;
        Float t = 1.f / rhs;
        for (int i = 0; i < 16; ++i)
            r.m[i] = m[i] * t;
        return r;
    }

    Matrix4x4 transpose() {
        Matrix4x4 r;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                r.v[i][j] = v[j][i];
        return r;
    }

    Float det() {
        return (
                m[3 ]*m[6 ]*m[9 ]*m[12] - m[2 ]*m[7 ]*m[9 ]*m[12] -
                m[3 ]*m[5 ]*m[10]*m[12] + m[1 ]*m[7 ]*m[10]*m[12] +
                m[2 ]*m[5 ]*m[11]*m[12] - m[1 ]*m[6 ]*m[11]*m[12] -
                m[3 ]*m[6 ]*m[8 ]*m[13] + m[2 ]*m[7 ]*m[8 ]*m[13] +
                m[3 ]*m[4 ]*m[10]*m[13] - m[0 ]*m[7 ]*m[10]*m[13] -
                m[2 ]*m[4 ]*m[11]*m[13] + m[0 ]*m[6 ]*m[11]*m[13] +
                m[3 ]*m[5 ]*m[8 ]*m[14] - m[1 ]*m[7 ]*m[8 ]*m[14] -
                m[3 ]*m[4 ]*m[9 ]*m[14] + m[0 ]*m[7 ]*m[9 ]*m[14] +
                m[1 ]*m[4 ]*m[11]*m[14] - m[0 ]*m[5 ]*m[11]*m[14] -
                m[2 ]*m[5 ]*m[8 ]*m[15] + m[1 ]*m[6 ]*m[8 ]*m[15] +
                m[2 ]*m[4 ]*m[9 ]*m[15] - m[0 ]*m[6 ]*m[9 ]*m[15] -
                m[1 ]*m[4 ]*m[10]*m[15] + m[0 ]*m[5 ]*m[10]*m[15]
        );
    }

    Matrix4x4 inverse() {
        Matrix4x4 r;
        Float det;

        r.m[0] = m[5]  * m[10] * m[15] - 
                 m[5]  * m[11] * m[14] - 
                 m[9]  * m[6]  * m[15] + 
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] - 
                 m[13] * m[7]  * m[10];

        r.m[4] = -m[4]  * m[10] * m[15] + 
                  m[4]  * m[11] * m[14] + 
                  m[8]  * m[6]  * m[15] - 
                  m[8]  * m[7]  * m[14] - 
                  m[12] * m[6]  * m[11] + 
                  m[12] * m[7]  * m[10];

        r.m[8] = m[4]  * m[9] * m[15] - 
                 m[4]  * m[11] * m[13] - 
                 m[8]  * m[5] * m[15] + 
                 m[8]  * m[7] * m[13] + 
                 m[12] * m[5] * m[11] - 
                 m[12] * m[7] * m[9];

        r.m[12] = -m[4]  * m[9] * m[14] + 
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5] * m[14] - 
                   m[8]  * m[6] * m[13] - 
                   m[12] * m[5] * m[10] + 
                   m[12] * m[6] * m[9];

        r.m[1] = -m[1]  * m[10] * m[15] + 
                  m[1]  * m[11] * m[14] + 
                  m[9]  * m[2] * m[15] - 
                  m[9]  * m[3] * m[14] - 
                  m[13] * m[2] * m[11] + 
                  m[13] * m[3] * m[10];

        r.m[5] = m[0]  * m[10] * m[15] - 
                 m[0]  * m[11] * m[14] - 
                 m[8]  * m[2] * m[15] + 
                 m[8]  * m[3] * m[14] + 
                 m[12] * m[2] * m[11] - 
                 m[12] * m[3] * m[10];

        r.m[9] = -m[0]  * m[9] * m[15] + 
                  m[0]  * m[11] * m[13] + 
                  m[8]  * m[1] * m[15] - 
                  m[8]  * m[3] * m[13] - 
                  m[12] * m[1] * m[11] + 
                  m[12] * m[3] * m[9];

        r.m[13] = m[0]  * m[9] * m[14] - 
                  m[0]  * m[10] * m[13] - 
                  m[8]  * m[1] * m[14] + 
                  m[8]  * m[2] * m[13] + 
                  m[12] * m[1] * m[10] - 
                  m[12] * m[2] * m[9];

        r.m[2] = m[1]  * m[6] * m[15] - 
                 m[1]  * m[7] * m[14] - 
                 m[5]  * m[2] * m[15] + 
                 m[5]  * m[3] * m[14] + 
                 m[13] * m[2] * m[7] - 
                 m[13] * m[3] * m[6];

        r.m[6] = -m[0]  * m[6] * m[15] + 
                  m[0]  * m[7] * m[14] + 
                  m[4]  * m[2] * m[15] - 
                  m[4]  * m[3] * m[14] - 
                  m[12] * m[2] * m[7] + 
                  m[12] * m[3] * m[6];

        r.m[10] = m[0]  * m[5] * m[15] - 
                  m[0]  * m[7] * m[13] - 
                  m[4]  * m[1] * m[15] + 
                  m[4]  * m[3] * m[13] + 
                  m[12] * m[1] * m[7] - 
                  m[12] * m[3] * m[5];

        r.m[14] = -m[0]  * m[5] * m[14] + 
                   m[0]  * m[6] * m[13] + 
                   m[4]  * m[1] * m[14] - 
                   m[4]  * m[2] * m[13] - 
                   m[12] * m[1] * m[6] + 
                   m[12] * m[2] * m[5];

        r.m[3] = -m[1] * m[6] * m[11] + 
                  m[1] * m[7] * m[10] + 
                  m[5] * m[2] * m[11] - 
                  m[5] * m[3] * m[10] - 
                  m[9] * m[2] * m[7] + 
                  m[9] * m[3] * m[6];

        r.m[7] = m[0] * m[6] * m[11] - 
                 m[0] * m[7] * m[10] - 
                 m[4] * m[2] * m[11] + 
                 m[4] * m[3] * m[10] + 
                 m[8] * m[2] * m[7] - 
                 m[8] * m[3] * m[6];

        r.m[11] = -m[0] * m[5] * m[11] + 
                   m[0] * m[7] * m[9] + 
                   m[4] * m[1] * m[11] - 
                   m[4] * m[3] * m[9] - 
                   m[8] * m[1] * m[7] + 
                   m[8] * m[3] * m[5];

        r.m[15] = m[0] * m[5] * m[10] - 
                  m[0] * m[6] * m[9] - 
                  m[4] * m[1] * m[10] + 
                  m[4] * m[2] * m[9] + 
                  m[8] * m[1] * m[6] - 
                  m[8] * m[2] * m[5];

        det = m[0] * r.m[0] + m[1] * r.m[4] + m[2] * r.m[8] + m[3] * r.m[12];
        assert(det != 0);

        return r / det;
    }
};

VSRAY_NAMESPACE_END
