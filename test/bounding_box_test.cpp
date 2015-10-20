#include <gtest/gtest.h>
#include "common/common.h"
#include "bounding_box.h"
#include "mesh_factory.h"
#include "assertions.h"


TEST(BoundingBox, FindsRightBoundariesForCube) {
    BoundingBox f(MeshFactory::basicCube(-1, -1, -1, 1, 1, 1));

    ASSERT_EQ(Vec(-1, -1, -1), f.getMinBoundaries());
    ASSERT_EQ(Vec(1, 1, 1), f.getMaxBoundaries());
    ASSERT_EQ(Vec(0, 0, 0), f.getCenter());


}

TEST(BoundingBox, subdivide) {
    BoundingBox bb(Vec(1, 0, 0), Vec(2, 1, 1));
    vector<BoundingBox> subdivisions = bb.subdivisions();

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0, 0), subdivisions[0].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0.5), subdivisions[0].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0, 0), subdivisions[1].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 0.5, 0.5), subdivisions[1].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0.5, 0), subdivisions[2].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 1, 0.5), subdivisions[2].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0, 0.5), subdivisions[3].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 1), subdivisions[3].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0.5, 0.5), subdivisions[4].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 1, 1), subdivisions[4].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0, 0.5), subdivisions[5].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 0.5, 1), subdivisions[5].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0), subdivisions[6].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 1, 0.5), subdivisions[6].getMaxBoundaries()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0.5), subdivisions[7].getMinBoundaries()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 1, 1), subdivisions[7].getMaxBoundaries()));

}

TEST(BoundingBox, correctlyCenterMeshVertices) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    BoundingBox::centerMeshVertices(mesh);

    Vec P1(-.5, -0.5, -0.5), P2(0.5, 0.5, 0.5);
    bool hasP1 = false, hasP2 = false;
    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {

        if (mesh.point(*it) == P1) {
            hasP1 = true;
        }
        if (mesh.point(*it) == P2) {
            hasP2 = true;
        }
    }

    ASSERT_TRUE(hasP1);
    ASSERT_TRUE(hasP2);


}