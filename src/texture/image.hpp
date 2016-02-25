#pragma once

#include "core/texture.hpp"
#include "core/spectrum.hpp"
#include "core/intersection.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

VSRAY_NAMESPACE_BEGIN

class ImageTexture : public Texture<Spectrum> {
public:
    ImageTexture(string filename) {
        image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);
        assert(image.data);
        cntU = (real)image.cols;
        cntV = (real)image.rows;
    }

    virtual Spectrum evaluate(const Intersection &is) {
        int u = int(cntU * is.mapU);
        int v = int(cntV * is.mapV);
        if (u < 0 || v < 0 || u >= cntU) {
            printf("%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
                   is.mapU, is.mapV, is.u, is.v,
                   ((Mesh *)is.shape)->ua, ((Mesh *)is.shape)->va,
                   ((Mesh *)is.shape)->ub, ((Mesh *)is.shape)->vb,
                   ((Mesh *)is.shape)->uc, ((Mesh *)is.shape)->vc);
        }
        if (u == cntU) --u;
        if (v == cntV) --v;
        assert(0 <= u);
        assert(0 <= v);
        assert(u < cntU);
        assert(v < cntV);
        auto col = image.at<cv::Vec3b>(v, u);
        return Spectrum(real(col[2]) / 255.f,
                        real(col[1]) / 255.f,
                        real(col[0]) / 255.f);
    }

private:
    cv::Mat image;
    real cntU;
    real cntV;
};

VSRAY_NAMESPACE_END
