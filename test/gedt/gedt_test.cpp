#include <gtest/gtest.h>
#include "gedt/gedt.h"
#include "mesh_factory.h"

TEST(GEDT, ConstructsCorrectly) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    GEDT f(mesh, 4);

    for (float x = 0; x < 1.0; x += (1. / 10)) {
        for (float y = 0; y < 1.0; y += (1. / 10)) {
            for (float z = 0; z < 1.0; z += (1. / 10)) {
                ASSERT_LE(f(Vec(x, y, z)), 1.0);
                ASSERT_GE(f(Vec(x, y, z)), 0.0);
            }
        }
    }
}