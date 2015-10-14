#include <gtest/gtest.h>
#include "common/common.h"
#include "bounding_box.h"
#include "test_util/mesh_factory.h"


TEST(BoundingBox, FindsRightBoundariesForCube) {
    BoundingBox f(MeshFactory::basicCube(-1, -1, -1, 1, 1, 1));

    ASSERT_EQ(Point(-1, -1, -1), f.getMinBoundaries());
    ASSERT_EQ(Point(1, 1, 1), f.getMaxBoundaries());
    ASSERT_EQ(Point(0, 0, 0), f.getCenter());


}