#include "core/mcmc.hpp"
#include "core/sample.hpp"
#include "core/sampler.hpp"
#include "core/ray.hpp"
#include "camera/perspective.hpp"

VSRAY_NAMESPACE_BEGIN

PerspCamera::PerspCamera(
        const Point &from,
        const Vector &to,
        const Vector &up,
        Float width,
        Float height,
        Float depth,
        Float lensRadius,
        Float focalDistance):
    Camera(from, to, up),
    width(width), height(height), depth(depth),
    lensRadius(lensRadius), focalDistance(focalDistance)
{
    // pass
}

void PerspCamera::genRay(const Sample &sample, Ray *ray)
{
    Float x = (sample.imageX - 0.5f) * width;
    Float y = (sample.imageY - 0.5f) * height;

    ray->o = Point(0, 0, 0);
    ray->d = Vector(x, y, depth);

    modifyRayDOF(sample, ray);

    ray->o = cameraToWorld(ray->o);
    ray->d = cameraToWorld(ray->d).normalize();
}

void PerspCamera::modifyRayDOF(const Sample &sample, Ray *ray)
{
    if (lensRadius > 0.f) {
        Point p = ray->o + ray->d * (lensRadius / ray->d.z);

        Vector v;
        uniformDisk(sample.lensU, sample.lensV, &v.x, &v.y);

        ray->o += v;
        ray->d = (p - ray->o).normalize();
    }
}

VSRAY_NAMESPACE_END
