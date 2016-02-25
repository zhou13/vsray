#include "core/film.hpp"
#include "core/filter.hpp"
#include "core/sample.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <mutex>

VSRAY_NAMESPACE_BEGIN

Film::Film(int width, int height, Filter *filter, string filename) :
    width(width), height(height), filter(filter), filename(filename)
{
    image = new Pixel[width * height];
    dx = dy = filter->size;
}

Film::~Film()
{
    delete[] image;
    delete filter;
}

void Film::setFilename(const string &filename_)
{
    filename = filename_;
}

static std::mutex filmMutex;

void Film::addSample(const Sample &sample, Spectrum sp)
{
    std::unique_lock<std::mutex> lock(filmMutex);

    real x = (real)width  * sample.imageX;
    real y = (real)height * (1 - sample.imageY);

    int i0 = (int)std::max(ceil(y-dy), 0.f);
    int j0 = (int)std::max(ceil(x-dx), 0.f);
    int i1 = (int)std::min(floor(y+dy), (real)height - 0.5f);
    int j1 = (int)std::min(floor(x+dx), (real)width - 0.5f);

    for (int i = i0; i <= i1; ++i)
        for (int j = j0; j <= j1; ++j) {
            real weight = (*filter)(real(j) - x, real(i) - y);
            image[i * width + j].color += sp * weight;
            image[i * width + j].weight += weight;
        }
}

void Film::clear()
{
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            image[i * width + j].color = 0.;
            image[i * width + j].weight = 0;
        }

}

void Film::saveToDisk()
{
    std::unique_lock<std::mutex> lock(filmMutex);

    using namespace cv;

    Mat img(height, width, CV_8UC3, Scalar::all(0));

    uint8_t *m = (uint8_t *)(img.data);
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j) {
            int k = i * width + j;
            real rgb[3];

            if (image[k].weight == 0.f) {
                rgb[0] = rgb[1] = 0.f;
                rgb[2] = 1.f;
            } else {
                (image[k].color / image[k].weight).getRGB(rgb);
            }
            m[i * (int)img.step + j * 3 + 0] = (uint8_t)clamp(rgb[2] * 255, 0, 255);
            m[i * (int)img.step + j * 3 + 1] = (uint8_t)clamp(rgb[1] * 255, 0, 255);
            m[i * (int)img.step + j * 3 + 2] = (uint8_t)clamp(rgb[0] * 255, 0, 255);
        }

    imwrite(filename, img);
}

VSRAY_NAMESPACE_END
