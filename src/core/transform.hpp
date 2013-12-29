#pragma once

#include "core/geometry.hpp"
#include "core/matrix.hpp"

VSRAY_NAMESPACE_BEGIN

class Transform {
public:
    Matrix4x4 mat;
    shared_ptr<Matrix4x4> invTr;

    Transform() { }

    explicit Transform(Matrix4x4 mat_) : mat(mat_) { }

    Transform inverse() {
        return Transform(mat.inverse());
    }

    Transform operator *(const Transform &rhs) {
        return Transform(mat * rhs.mat);
    }

    Point operator()(const Point &p) {
        Matrix4x1 m(p);
        // pobj(mat*m);
        // pobj(Point(mat * m));
        return Point(mat * m);
    }

    Vector operator()(const Vector &p) {
        Matrix4x1 m(p);
        return Vector(mat * m);
    }

    Normal operator()(const Normal &p) {
        if (invTr == nullptr)
            invTr = make_shared<Matrix4x4>(mat.inverse().transpose());
        Matrix4x1 m(p);
        return Normal(*invTr * m);
    }

    string toString() {
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

        m[0][1] = up.x;
        m[1][1] = up.y;
        m[2][1] = up.z;

        m[0][2] = to.x;
        m[1][2] = to.y;
        m[2][2] = to.z;

        return Transform(Matrix4x4((real *)m));
    }
};

VSRAY_NAMESPACE_END
