#include <gtest/gtest.h>
#include <array>
#include "gedt/octree.h"
#include "common/common.h"
#include "factory/mesh_factory.h"

using std::array;

TEST(Grid, coordPointConversion) {
    Grid grid(BoundingBox(Vec(-1, 0, 0), Vec(3, 1, 1)), 4);


    ASSERT_EQ(Vec3i(3, 3, 3), grid.coordsFromPoint(Vec(2.5, 0.875, 0.875)));
    ASSERT_EQ(Vec3i(0, 0, 0), grid.coordsFromPoint(Vec(-0.5, 0.125, 0.125)));
    ASSERT_EQ(Vec3i(2, 1, 1), grid.coordsFromPoint(Vec(1.5, 0.375, 0.375)));

    ASSERT_EQ(Vec(2.5, 0.875, 0.875), grid.voxelCenterFromCoords(Vec3i(3, 3, 3)));
    ASSERT_EQ(Vec(-0.5, 0.125, 0.125), grid.voxelCenterFromCoords(Vec3i(0, 0, 0)));
    ASSERT_EQ(Vec(1.5, 0.375, 0.375), grid.voxelCenterFromCoords(Vec3i(2, 1, 1)));
}