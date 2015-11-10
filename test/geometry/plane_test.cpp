#include <gtest/gtest.h>

#include "common/common.h"
#include "geometry/plane.h"
#include "assertions.h"

TEST(Plane, cartesianProjection) {
    Vec H = Plane::projectPointOnCartesianPlane(Vec(0, 0, 0), Vec(0, 0, 1), Vec(1, 1, 1));
    ASSERT_EQ(Vec(0, 0, 1), H);
    H = Plane::projectPointOnCartesianPlane(Vec(0, 2, 0), Vec(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0), Vec(0, 0, 0));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 1, 0), H));
}

TEST(Plane, cartesianToSpherical) {
    Plane p = Plane::fromCartesian(Vec(0, 0, 1), Vec(1, 1, 1));
    ASSERT_DOUBLE_EQ(1, p.r);
    ASSERT_DOUBLE_EQ(0, p.theta);
    ASSERT_DOUBLE_EQ(0, p.phi);

    Vec n(1.25, 2.165063509, 4.330127019);
    p = Plane::fromCartesian(n.normalized(), n);
    ASSERT_NEAR(5, p.r, 1e-7);
    ASSERT_NEAR(M_PI / 6, p.theta, 1e-7);
    ASSERT_NEAR(M_PI / 3, p.phi, 1e-7);

    n = Vec(0, 0.8660254038, -0.5);
    p = Plane::fromCartesian(n.normalized(), n);
    ASSERT_NEAR(-1, p.r, 1e-7);
    ASSERT_NEAR(M_PI / 3, p.theta, 1e-7);
    ASSERT_NEAR(3 * M_PI / 2, p.phi, 1e-7);
}

