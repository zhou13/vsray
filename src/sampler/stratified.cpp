#include "sampler/stratified.hpp"
#include "core/random.hpp"
#include "core/sample.hpp"

VSRAY_NAMESPACE_BEGIN

const int MAX_SAMPLES = 100;

StratifiedSampler::StratifiedSampler(
        int imageWidth,
        int imageHeight,
        int nSamplePerPixel,
        int nLight,
        int nBSDF,
        bool stratified) :
    Sampler(nLight, nBSDF),
    imageWidth(imageWidth),
    imageHeight(imageHeight),
    nSamplePerPixel(nSamplePerPixel),
    stratified(stratified), initialized(false)
{
    imageX = nullptr;
    imageX = nullptr;
    imageY = nullptr;
    lensU = nullptr;
    lensV = nullptr;
}

StratifiedSampler::~StratifiedSampler()
{
    delete[] imageX;
    delete[] imageY;
    delete[] lensU;
    delete[] lensV;
}

Sampler *StratifiedSampler::duplicate()
{
    return new StratifiedSampler(
            imageWidth,
            imageHeight,
            nSamplePerPixel,
            nLight, nBSDF,
            stratified);
}

void StratifiedSampler::initialize(int x0, int x1, int y0, int y1)
{
    width = x1 - x0;
    height = y1 - y0;

    numSamplesLeft = numSamples = width * height * nSamplePerPixel;
    imageX = new real[numSamples];
    imageY = new real[numSamples];
    lensU  = new real[numSamples];
    lensV  = new real[numSamples];

    int i = 0;
    for (int x = x0; x < x1; ++x)
        for (int y = y0; y < y1; ++y)
            for (int k = 0; k < nSamplePerPixel; ++k) {
            imageX[i] = 1.f / (real)imageWidth  * ((real)x + offset());
            imageY[i] = 1.f / (real)imageHeight * ((real)y + offset());
            ++i;
        }

    int n = (int)sqrt(width * height);
    for (int x = 0; x < n; ++x)
        for (int y = 0; y < n; ++y)
            for (int k = 0; k < nSamplePerPixel; ++k) {
                --i;
                lensU[i]  = 1.f / (real)n * ((real)x + offset());
                lensV[i]  = 1.f / (real)n * ((real)y + offset());
            }
    while (i > 0) {
        --i;
        lensU[i] = random.nextRandomReal();
        lensV[i] = random.nextRandomReal();
    }

    for (i = 0; i < numSamples; ++i) {
        int j = random.nextRandomInt(0, numSamples);
        std::swap(lensU[i], lensU[j]);
        std::swap(lensV[i], lensV[j]);
    }

    initialized = true;
}

bool StratifiedSampler::genSamples(Sample *samples, int *n)
{
    assert(initialized);
    *n = 0;
    while (numSamplesLeft > 0 && *n < MAX_SAMPLES) {
        int i = numSamples - numSamplesLeft;
        --numSamplesLeft;

        samples[*n].imageX = imageX[i];
        samples[*n].imageY = imageY[i];
        samples[*n].lensU = lensU[i];
        samples[*n].lensV = lensV[i];

        samples[*n].nLight = nLight;
        samples[*n].nBSDF = nBSDF;
        samples[*n].idxLight = 0;
        samples[*n].idxBSDF = 0;

        genStratified1D(&samples[*n].lightU, nLight);
        genStratified1D(&samples[*n].lightV, nLight);
        genStratified1D(&samples[*n].lightI, nLight);
        genStratified1D(&samples[*n].lightJ, nLight);
        genStratified1D(&samples[*n].bxdfU, nBSDF);
        genStratified1D(&samples[*n].bxdfV, nBSDF);
        genStratified1D(&samples[*n].bxdfI, nBSDF);

        checkOne(samples[*n].lightI, nLight);
        checkOne(samples[*n].lightJ, nLight);

        (*n) += 1;
    }

    return numSamplesLeft > 0;
}

int StratifiedSampler::getSamplesCount()
{
    return std::min(MAX_SAMPLES, numSamples);
}

int StratifiedSampler::roundSize(int size)
{
    return size;
}

real StratifiedSampler::offset()
{
    if (stratified)
        return random.nextRandomReal();
    return .5f;
}

void StratifiedSampler::genStratified1D(real **f, int n)
{
    if (*f == nullptr)
        *f = new real[n];

    real gap = 1.f / (real)n;
    for (int i = 0; i < n; ++i)
        (*f)[i] = ((real)i + offset()) * gap;
    for (int i = 0; i < n; ++i)
        std::swap((*f)[i], (*f)[random.nextRandomInt(n)]);
}

void StratifiedSampler::checkOne(real *f, int n)
{
    for (int i = 0; i < n; ++i)
        if (f[i] >= 1.f) {
            union {
                real f;
                intflt_t i;
            } c;
            c.f = f[i];
            --c.i;
            f[i] = c.f;
        }
}


VSRAY_NAMESPACE_END
