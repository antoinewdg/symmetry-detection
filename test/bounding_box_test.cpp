#include <gtest/gtest.h>
#include "common/common.h"
#include "bounding_box.h"
#include "factory/mesh_factory.h"
#include "assertions.h"


TEST(BoundingBox, FindsRightBoundariesForCube) {
    BoundingBox f(MeshFactory::basicCube(0, 0, 0, 2, 2, 2));

    ASSERT_EQ(Vec(-0.2, -0.2, -0.2), f.getMin());
    ASSERT_EQ(Vec(2.2, 2.2, 2.2), f.getMax());
    ASSERT_EQ(Vec(1, 1, 1), f.getCenter());


}

TEST(BoundingBox, subdivide) {
    BoundingBox bb(Vec(1, 0, 0), Vec(2, 1, 1));
    vector<BoundingBox> subdivisions = bb.subdivisions();

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0, 0), subdivisions[0].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0.5), subdivisions[0].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0, 0), subdivisions[1].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 0.5, 0.5), subdivisions[1].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0.5, 0), subdivisions[2].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 1, 0.5), subdivisions[2].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0, 0.5), subdivisions[3].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 1), subdivisions[3].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1, 0.5, 0.5), subdivisions[4].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 1, 1), subdivisions[4].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0, 0.5), subdivisions[5].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 0.5, 1), subdivisions[5].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0), subdivisions[6].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 1, 0.5), subdivisions[6].getMax()));

    ASSERT_TRUE(AreVecAlmostEqual(Vec(1.5, 0.5, 0.5), subdivisions[7].getMin()));
    ASSERT_TRUE(AreVecAlmostEqual(Vec(2, 1, 1), subdivisions[7].getMax()));

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