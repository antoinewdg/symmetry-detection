#include <gtest/gtest.h>
#include <array>
#include "gedt/octree.h"
#include "common/common.h"
#include "factory/mesh_factory.h"

using std::array;


TEST(OCTree, Contruction) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));
    OCTree tree(mesh, BoundingBox(Vec(-0.01, -0.01, -0.01), Vec(1.01, 1.01, 1.01)), 3);
    tree.computeMesh(faces);
    for (int z = 1; z < 7; z++) {
        ASSERT_EQ(2, tree.getVoxelValue(0, 0, z));
        ASSERT_EQ(2, tree.getVoxelValue(7, 0, z));
        ASSERT_EQ(2, tree.getVoxelValue(7, 7, z));
        ASSERT_EQ(2, tree.getVoxelValue(0, 7, z));
        for (int y = 1; y < 7; y++) {
            ASSERT_EQ(1, tree.getVoxelValue(0, y, z));
            ASSERT_EQ(1, tree.getVoxelValue(7, y, z));
        }
        for (int x = 1; x < 7; x++) {
            ASSERT_EQ(1, tree.getVoxelValue(x, 0, z));
            ASSERT_EQ(1, tree.getVoxelValue(x, 7, z));
        }
        for (int y = 1; y < 7; y++) {
            for (int x = 1; x < 7; x++) {
                ASSERT_EQ(0, tree.getVoxelValue(x, y, z));
            }
        }

    }
    for (int z = 0; z < 8; z += 7) {
        ASSERT_EQ(3, tree.getVoxelValue(0, 0, z));
        ASSERT_EQ(3, tree.getVoxelValue(7, 0, z));
        ASSERT_EQ(3, tree.getVoxelValue(7, 7, z));
        ASSERT_EQ(3, tree.getVoxelValue(0, 7, z));
        for (int y = 1; y < 7; y++) {
            ASSERT_EQ(2, tree.getVoxelValue(0, y, z));
            ASSERT_EQ(2, tree.getVoxelValue(7, y, z));
        }
        for (int x = 1; x < 7; x++) {
            ASSERT_EQ(2, tree.getVoxelValue(x, 0, z));
            ASSERT_EQ(2, tree.getVoxelValue(x, 7, z));
        }
        for (int y = 1; y < 7; y++) {
            for (int x = 1; x < 7; x++) {
                ASSERT_EQ(1, tree.getVoxelValue(x, y, z));
            }
        }
    }

}


TEST(OCTree, handlesLargeDepth) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));
    OCTree tree(mesh, BoundingBox(Vec(-0.01, -0.01, -0.01), Vec(1.01, 1.01, 1.01)), 6);
    tree.computeMesh(faces);
}