#ifndef __VSRAY__HEADER
#define __VSRAY__HEADER

#define VSRAY_NAMESPACE_BEGIN namespace vsray {
#define VSRAY_NAMESPACE_END   }

// C Library
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// C++ Library
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>

#ifndef DOUBLE_PRECISION
#ifndef SINGLE_PRECISION
#define SINGLE_PRECISION
#endif
#endif

namespace vsray {
#ifdef DOUBLE_PRECISION
    typedef double real;
    typedef uint64_t intflt_t;
    const float FLOAT_RELATIVE = 5e-8f;
#else
    typedef float real;
    typedef uint32_t intflt_t;
    const float FLOAT_RELATIVE = 5e-5f;
#endif
    const real PI = real(3.141592653589793238462);
    const real INV_PI = 1.f / PI;
}

#include <boost/lexical_cast.hpp>
#include <boost/pool/object_pool.hpp>

namespace vsray {
    using std::abs;
    using std::sin;
    using std::cos;
    using std::tan;
    using std::acos;
    using std::asin;
    using std::atan;
    using std::atan2;
    using std::sqrt;
    using std::exp;
    using std::log;
    using std::log2;
    using std::ceil;
    using std::floor;

    using std::tuple;
    using std::tie;
    using std::make_tuple;

    using std::string;
    using std::vector;
    using std::shared_ptr;
    using std::make_shared;

    using boost::lexical_cast;
    using boost::object_pool;
}

#define pobj(x) fprintf(stderr, "[%s::%d] %s\n", __FILE__, __LINE__, (x).toString().c_str())
#define pdash() fprintf(stderr, "============================================================\n")
#define UNUSED(x) (void)x

#endif
