#pragma once

#include "core/geometry.hpp"
#include "core/bbox.hpp"
#include "core/matrix.hpp"

VSRAY_NAMESPACE_BEGIN

class Transform {
public:
    Matrix4x4 mat;
    mutable shared_ptr<Matrix4x4> invTr;

    Transform() { }

    explicit Transform(Matrix4x4 mat_) : mat(mat_) { }

    Transform inverse() const {
        return Transform(mat.inverse());
    }

    Transform operator *(const Transform &rhs) const {
        return Transform(mat * rhs.mat);
    }

    inline Point operator()(const Point &p) const {
        Matrix4x1 m(p);
        // pobj(mat*m);
        // pobj(Point(mat * m));
        return Point(mat * m);
    }

    inline Vector operator()(const Vector &p) const {
        Matrix4x1 m(p);
        return Vector(mat * m);
    }

    inline Normal operator()(const Normal &p) const {
        if (invTr == nullptr)
            invTr = make_shared<Matrix4x4>(mat.inverse().transpose());
        Matrix4x1 m(p);
        return Normal(*invTr * m);
    }

    inline Ray operator()(const Ray &in) const {
        Ray ret = in;
        ret.o = (*this)(in.o);
        ret.d = (*this)(in.d);
        return ret;
    }

    inline BBox operator()(const BBox &in) const {
        BBox ret;
        Point p0(in.x0, in.y0, in.z0);
        Point p1(in.x1, in.y1, in.z1);
        p0 = (*this)(p0);
        p1 = (*this)(p1);
        ret.x0 = p0.x;
        ret.y0 = p0.y;
        ret.z0 = p0.z;
        ret.x1 = p1.x;
        ret.y1 = p1.y;
        ret.z1 = p1.z;
        return ret;
    }

    string toString() const {
        return mat.toString();
    }

    static Transform translate(const Vector &d) {
        Matrix4x4 m(1);
        m.v[0][3] = d.x;
        m.v[1][3] = d.y;
        m.v[2][3] = d.z;
        return Transform(m);
    }

    static Transform scale(const Vector &d) {
        Matrix4x4 m;
        m.v[0][0] = d.x;
        m.v[1][1] = d.y;
        m.v[2][2] = d.z;
        return Transform(m);
    }

    static Transform rotateX(real t) {
        real sint = sin(t);
        real cost = cos(t);
        Matrix4x4 m(
                1.f, 0.f, 0.f, 0.f,
                0.f, cost, -sint, 0.f,
                0.f, sint, +cost, 0.f,
                0.f, 0.f, 0.f, 1.f
        );
        return Transform(m);
    }

    static Transform rotateY(real t) {
        real sint = sin(t);
        real cost = cos(t);
        Matrix4x4 m(
                cost, 0.f, sint, 0.f,
                0.f, 1.f, 0.f, 0.f,
                -sint, 0.f, cost, 0.f,
                0.f, 0.f, 0.f, 1.f
        );
        return Transform(m);
    }

    static Transform rotateZ(real t) {
        real sint = sin(t);
        real cost = cos(t);
        Matrix4x4 m(
                cost, -sint, 0.f, 0.f,
                sint, cost, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f
        );
        return Transform(m);
    }

    static Transform lookAt(const Point &from,
                            const Vector &to,
                            const Vector &up)
    {
        real m[4][4];
        
        m[0][3] = from.x;
        m[1][3] = from.y;
        m[2][3] = from.z;
        m[3][3] = 1;

        m[3][0] = m[3][1] = m[3][2] = 0;

        Vector vx = up.cross(to);
        m[0][0] = vx.x;
        m[1][0] = vx.y;
        m[2][0] = vx.z;

        Vector up2 = to.cross(vx);
        m[0][1] = up2.x;
        m[1][1] = up2.y;
        m[2][1] = up2.z;

        m[0][2] = to.x;
        m[1][2] = to.y;
        m[2][2] = to.z;

        return Transform(Matrix4x4((real *)m));
    }
};

VSRAY_NAMESPACE_END
