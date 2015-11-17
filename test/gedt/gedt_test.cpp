#include <gtest/gtest.h>
#include "gedt/gedt.h"
#include "factory/mesh_factory.h"

TEST(GEDT, ConstructsCorrectly) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    GEDT f(mesh, 4);

    for (float x = -0.5f; x <= 0.5f; x += (1.f / 3)) {
        for (float y = -0.5f; y <= 0.5f; y += (1.f / 3)) {
//            std::cout << f(Vec(x, y, 0.5)) << " ";
            for (float z = -0.5f; z <= 0.5f; z += (1.f / 3)) {
//                std::cout << f(Vec(x, y, z)) << " ";
                ASSERT_LE(f(Vec(x, y, z)), 1.0);
                ASSERT_GE(f(Vec(x, y, z)), 0.0);
            }
        }
//        std::cout << std::endl;
    }


}