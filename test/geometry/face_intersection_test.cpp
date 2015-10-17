#include <gtest/gtest.h>

#include "geometry/face_intersection.h"
#include "mesh_factory.h"
#include "bounding_box.h"

TEST(FaceIntersection, WorksWithTriangles) {
    vector<Vec> triangle = {Vec(0, 0, 0), Vec(2, 0, 0), Vec(0, 2, 1)};
//    Mesh triangle = MeshFactory::triangle(Vec(0.5, 0.5, 0.5), Vec(2, 0.5, 1), Vec(0.5, 2, 0.5));
    BoundingBox bb(Vec(0, 0, 0), Vec(1, 1, 1));


    ASSERT_TRUE(FaceIntersection::faceIntersectsBoundingBox(bb, triangle));

    triangle = {Vec(8, 8, 8), Vec(8, 8, 9), Vec(9, 9, 9)};
    ASSERT_FALSE(FaceIntersection::faceIntersectsBoundingBox(bb, triangle));
}

TEST(FaceIntersection, ProjectPointsOnAxis) {
    double min, max;
    FaceIntersection::projectPointsOnAxis(
            {Vec(2, 3, 2), Vec(2, 3, -5)},
            Vec(0, 0, 1), min, max
    );

    ASSERT_DOUBLE_EQ(min, -5);
    ASSERT_DOUBLE_EQ(max, 2);

    vector<Vec> points = {Vec(3.457, 4.478, -45), Vec(8.77, 0.222222, -1), Vec(0, 0, 0), Vec(-8, 7, 7)};
    Vec axis(1, 1, 1);

    FaceIntersection::projectPointsOnAxis(points, Vec(0, 0, 0), min, max);
    ASSERT_DOUBLE_EQ(min, 0);
    ASSERT_DOUBLE_EQ(max, 0);

    FaceIntersection::projectPointsOnAxis(points, axis, min, max);
    ASSERT_DOUBLE_EQ(min, points[0] | axis);
    ASSERT_DOUBLE_EQ(max, points[1] | axis);
}