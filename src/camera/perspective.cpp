#include "core/mcmc.hpp"
#include "core/sample.hpp"
#include "core/sampler.hpp"
#include "core/ray.hpp"
#include "camera/perspective.hpp"

VSRAY_NAMESPACE_BEGIN

PerspCamera::PerspCamera(
        const Transform &tr,
        real width,
        real height,
        real depth,
        real lensRadius,
        real focalDistance):
    Camera(tr), width(width), height(height), depth(depth),
    lensRadius(lensRadius), focalDistance(focalDistance)
{
    // pass
}

PerspCamera::PerspCamera(
        const Point &from,
        const Vector &to,
        const Vector &up,
        real width,
        real height,
        real depth,
        real lensRadius,
        real focalDistance):
    Camera(from, to, up),
    width(width), height(height), depth(depth),
    lensRadius(lensRadius), focalDistance(focalDistance)
{
    // pass
}

void PerspCamera::setFocalDistance(real focalDistance_)
{
    focalDistance = focalDistance_;
}

void PerspCamera::genRay(const Sample &sample, Ray *ray)
{
    real x = (sample.imageX - 0.5f) * width;
    real y = (sample.imageY - 0.5f) * height;

    ray->o = Point(0, 0, 0);
    ray->d = Vector(x, y, depth).normalize();

    modifyRayDOF(sample, ray);

    ray->o = cameraToWorld(ray->o);
    ray->d = cameraToWorld(ray->d);
}

void PerspCamera::modifyRayDOF(const Sample &sample, Ray *ray)
{
    if (lensRadius > 0.f) {
        Point p = ray->o + ray->d * (focalDistance / ray->d.z);

        Vector v;
        uniformDisk(sample.lensU, sample.lensV, &v.x, &v.y);

        ray->o += v * lensRadius;
        ray->d = (p - ray->o).normalize();
    }
}

VSRAY_NAMESPACE_END
