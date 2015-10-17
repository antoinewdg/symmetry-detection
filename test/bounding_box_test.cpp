#include <gtest/gtest.h>
#include "common/common.h"
#include "bounding_box.h"
#include "mesh_factory.h"


TEST(BoundingBox, FindsRightBoundariesForCube) {
    BoundingBox f(MeshFactory::basicCube(-1, -1, -1, 1, 1, 1));

    ASSERT_EQ(Vec(-1, -1, -1), f.getMinBoundaries());
    ASSERT_EQ(Vec(1, 1, 1), f.getMaxBoundaries());
    ASSERT_EQ(Vec(0, 0, 0), f.getCenter());


}