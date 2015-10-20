#include <gtest/gtest.h>
#include <cmath>
#include "common/common.h"
#include "spherical_coordinate_system.h"
#include "mesh_factory.h"


TEST(SphericalCoordinateSystem, ConstructorFitsMesh) {
    Mesh mesh = MeshFactory::basicCube(-1, -1, -1, 1, 1, 1);
    SphericalCoordinateSystem s(mesh);

    ASSERT_GE(s.getRadius(), std::sqrt(3.0));


}