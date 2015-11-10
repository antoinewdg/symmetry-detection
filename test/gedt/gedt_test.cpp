#include <gtest/gtest.h>
#include "gedt/gedt.h"
#include "factory/mesh_factory.h"

TEST(GEDT, ConstructsCorrectly) {
    Mesh mesh = MeshFactory::basicCube(0, 0, 0, 1, 1, 1);
    GEDT f(mesh, 4);

    for (float x = 0; x < 1.0; x += (1. / 3)) {
        for (float y = 0; y < 1.0; y += (1. / 3)) {
//            std::cout << f(Vec(x, y, 0.5)) << " ";
            for (float z = 0; z < 1.0; z += (1. / 3)) {
//                std::cout << f(Vec(x, y, z)) << " ";
                ASSERT_LE(f(Vec(x, y, z)), 1.0);
                ASSERT_GE(f(Vec(x, y, z)), 0.0);
            }
        }
//        std::cout << std::endl;
    }



//    ASSERT_EQ(64 * 64, f.getPointsOfInterest().size());


}