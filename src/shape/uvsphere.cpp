#include "shape/uvsphere.hpp"
#include "core/mcmc.hpp"
#include "shape/mesh.hpp"

VSRAY_NAMESPACE_BEGIN

UVSphere::UVSphere(
        const Point &center,
        real radius,
        int cntU,
        int cntV,
        bool inter,
        object_pool<Mesh> *pool)
{
    assert(cntU > 2);
    assert(cntV > 2);


    vector<vector<Vector>> ps(cntU);

    real invCntU = 1.f / real(cntU);
    real invCntV = 1.f / real(cntV);
    for (int i = 0; i < cntU; ++i) {
        for (int j = 0; j < cntV; ++j) {
            Vector dir;
            uniformSphere(invCntU * real(i), invCntV * real(j), &dir);
            ps[i].push_back(radius * dir);
        }
        ps[i].push_back(ps[i][0]);
    }

    for (int i = 0; i < cntU-1; ++i) {
        for (int j = 0; j < cntV; ++j) {
            Mesh *m1 = nullptr;
            Mesh *m2 = nullptr;
            if (!inter) {
                if (i > 0) {
                    m1 = pool->construct(
                            center + ps[i][j],
                            center + ps[i+1][j],
                            center + ps[i][j+1]
                    );
                }
                m2 = pool->construct(
                        center + ps[i+1][j+1],
                        center + ps[i][j+1],
                        center + ps[i+1][j]
                );
            } else {
                if (i > 0) {
                    m1 = pool->construct(
                            make_tuple(center + ps[i][j],
                                       center + ps[i+1][j],
                                       center + ps[i][j+1]),
                            make_tuple(Normal(ps[i][j]),
                                       Normal(ps[i+1][j]),
                                       Normal(ps[i][j+1]))
                    );
                }
                m2 = pool->construct(
                        make_tuple(center + ps[i+1][j+1],
                                   center + ps[i][j+1],
                                   center + ps[i+1][j]),
                        make_tuple(Normal(ps[i+1][j+1]),
                                   Normal(ps[i][j+1]),
                                   Normal(ps[i+1][j]))
                );
            }
            if (m1)
                addMesh(m1);
            addMesh(m2);
        }
    }
}

VSRAY_NAMESPACE_END
