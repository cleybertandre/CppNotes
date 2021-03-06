#ifndef UTILS_HPP
#define UTILS_HPP

#include <limits>
#include <cstdlib>

template<typename T>
bool equal(const T& left, const T& right) {
    return left == right;
}

template<>
bool equal<double>(const double& left, const double& right) {
    return std::fabs(left - right) <= std::numeric_limits<double>::epsilon();
}

bool equalDoubles(const double& left, const double& right,
                  const double& epsilon) {
    return std::fabs(left - right) <= epsilon;
}

#endif // UTILS_HPP

