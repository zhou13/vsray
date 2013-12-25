#pragma once

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
#include <cmath>

#ifndef DOUBLE_PRECISION
#ifndef SINGLE_PRECISION
#define SINGLE_PRECISION
#endif
#endif

namespace vsray {
#ifdef DOUBLE_PRECISION
    typedef double Float;
    typedef uint64_t intflt_t;
#else
    typedef float Float;
    typedef uint32_t intflt_t;
#endif
    const Float PI = Float(3.141592653589793238462);
    const Float PI = 1.f / PI;
}

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
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
    using std::ceil;
    using std::floor;

    using std::string;
    using std::vector;

    using boost::lexical_cast;
    using boost::shared_ptr;
    using boost::make_shared;
    using boost::object_pool;
}

#define pobj(x) fprintf(stderr, "Line(%d): %s\n", __LINE__, (x).toString().c_str())
#define pdash() fprintf(stderr, "============================================================\n")
