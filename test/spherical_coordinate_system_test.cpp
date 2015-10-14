#include <gtest/gtest.h>
#include <cmath>
#include "common/common.h"
#include "spherical_coordinate_system.h"
#include "test_util/mesh_factory.h"

TEST(SphericalCoordinateSystem, CorrectlyCenterMeshVertices) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    SphericalCoordinateSystem::centerMeshVertices(mesh);

    Point P1(-.5, -0.5, -0.5), P2(0.5, 0.5, 0.5);
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

TEST(SphericalCoordinateSystem, ConstructorFitsMesh) {
    Mesh mesh = MeshFactory::basicCube(-1, -1, -1, 1, 1, 1);
    SphericalCoordinateSystem s(mesh);

    ASSERT_FLOAT_EQ(s.getRadius(), std::sqrt(3.0));


}