//
// Created by antoinewdg on 18/10/15.
//

#ifndef SYMMETRY_DETECTION_ASSERTIONS_H
#define SYMMETRY_DETECTION_ASSERTIONS_H

#include <gtest/gtest.h>
#include "common/common.h"

inline ::testing::AssertionResult AreVecAlmostEqual(const Vec &u, const Vec &v, double epsilon = 1e-5) {
    bool success = true;
//    std::cout << "TESTING - u: " << u << " v: " << v << std::endl;
    for (int i = 0; i < 3; i++) {
        if (u[i] - v[i] > epsilon || v[i] - u[i] > epsilon) {
            success = false;
            break;
        }
    }
    if (success)
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure() << v << " is too far from " << u;
}

#endif //SYMMETRY_DETECTION_ASSERTIONS_H
