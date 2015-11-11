#include <gtest/gtest.h>

#include "geometry/face_intersection.h"
#include "factory/mesh_factory.h"
#include "bounding_box.h"

//TEST(FaceIntersection, WorksWithTriangles) {
//    vector<Vec> triangle = {Vec(0, 0, 0), Vec(2, 0, 0), Vec(0, 2, 1)};
////    Mesh triangle = MeshFactory::triangle(Vec(0.5, 0.5, 0.5), Vec(2, 0.5, 1), Vec(0.5, 2, 0.5));
//    BoundingBox bb(Vec(0, 0, 0), Vec(1, 1, 1));
//
//
//    ASSERT_TRUE(FaceIntersection::faceIntersectsBoundingBox(bb, triangle));
//
//    triangle = {Vec(8, 8, 8), Vec(8, 8, 9), Vec(9, 9, 9)};
//    ASSERT_FALSE(FaceIntersection::faceIntersectsBoundingBox(bb, triangle));
//}

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

TEST(FaceIntersection, projectPointOnPlane) {
    Vec A(0, 0, 0), n(0, 0, 1), M(3, 3, 8);
    ASSERT_EQ(Vec(3, 3, 0), FaceIntersection::projectPointOnPlane(M, n, A));

    M = Vec(-1.2, -8.2, 0);
    ASSERT_EQ(M, FaceIntersection::projectPointOnPlane(M, n, A));
}

TEST(FaceIntersection, isCoplanarPointInsideFace) {
    vector<Vec> points = {Vec(0, 0, 0), Vec(0, 1, 0), Vec(1, 2, 0), Vec(2, 1, 0), Vec(1, 0, 0)};

    ASSERT_FALSE(FaceIntersection::isCoplanarPointInsideFace(Vec(0, 0.5, 0), points));
    ASSERT_TRUE(FaceIntersection::isCoplanarPointInsideFace(Vec(0.5, 0.5, 0), points));
    ASSERT_FALSE(FaceIntersection::isCoplanarPointInsideFace(Vec(2, 2, 0), points));
}

TEST(FaceIntersection, pointToSegmentDistance) {
    Vec A(0, 1, 0), B(1, 0, 0);
    double epsilon = 0.000001;

    ASSERT_NEAR(0, FaceIntersection::pointToSegmentDistance(A, A, B), epsilon);
    ASSERT_NEAR(0, FaceIntersection::pointToSegmentDistance(B, A, B), epsilon);
    ASSERT_NEAR(std::sqrt(1.5), FaceIntersection::pointToSegmentDistance(Vec(1, 1, 1), A, B), epsilon);
    ASSERT_NEAR(std::sqrt(3), FaceIntersection::pointToSegmentDistance(Vec(-1, 2, 1), A, B), epsilon);
}

TEST(FaceIntersection, coplanarPointToFaceDistance) {
    vector<Vec> points = {Vec(0, 0, 0), Vec(0, 1, 0), Vec(1, 2, 0), Vec(2, 1, 0), Vec(1, 0, 0)};
    double epsilon = 0.000001;

    ASSERT_NEAR(0, FaceIntersection::coplanarPointToFaceDistance(Vec(0, 0.5, 0), points), epsilon);
    ASSERT_NEAR(0, FaceIntersection::coplanarPointToFaceDistance(Vec(0.5, 0.5, 0), points), epsilon);
    ASSERT_NEAR(std::sqrt(0.5), FaceIntersection::coplanarPointToFaceDistance(Vec(2, 2, 0), points), epsilon);
    ASSERT_NEAR(std::sqrt(5), FaceIntersection::coplanarPointToFaceDistance(Vec(4, 0, 0), points), epsilon);
}

TEST(FaceIntersection, faceSphereIntersection) {
    vector<Vec> points = {Vec(0, 0, 0), Vec(0, 1, 0), Vec(1, 2, 0), Vec(2, 1, 0), Vec(1, 0, 0)};
    Vec C(1, 1, 1);

    ASSERT_FALSE(FaceIntersection::faceSphereIntersection(points, C, 0.5));
    ASSERT_TRUE(FaceIntersection::faceSphereIntersection(points, C, 1.1));
    ASSERT_FALSE(FaceIntersection::faceSphereIntersection(points, Vec(2, 2, 1), std::sqrt(1.45)));
    ASSERT_TRUE(FaceIntersection::faceSphereIntersection(points, Vec(2, 2, 1), std::sqrt(1.55)));
}