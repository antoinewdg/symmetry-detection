//
// Created by AntoineWDG on 10/16/15.
//

#ifndef SYMMETRY_DETECTION_TRIANGLE_BOX_H
#define SYMMETRY_DETECTION_TRIANGLE_BOX_H

#include <cmath>
#include <array>
#include <vector>
#include <limits>
#include <algorithm>
#include <iterator>

#include "common/common.h"
#include "bounding_box.h"

using std::array;
using std::vector;

class FaceIntersection {
public:
    static bool faceIntersectsBoundingBox(BoundingBox bb, const vector<Vec> &points) {
        double triangleMin, triangleMax;
        double boxMin, boxMax;

        std::copy(points.begin(), points.end(), std::ostream_iterator<Vec>(std::cout, " -- "));

        // Test the box normals (x-, y- and z-axes)
        array<Vec, 3> boxNormals = {
                Vec(1, 0, 0),
                Vec(0, 1, 0),
                Vec(0, 0, 1)
        };
        for (int i = 0; i < 3; i++) {
            Vec n = boxNormals[i];
            projectPointsOnAxis(points, boxNormals[i], triangleMin, triangleMax);
            if (triangleMax < bb.getMinBoundaries()[i] || triangleMin > bb.getMaxBoundaries()[i])
                return false; // No intersection possible.
        }

        vector<Vec> edges(points.size());
        for (int i = 0; i < edges.size(); i++) {
            edges[i] = points[(i + 1) % edges.size()] - points[i];
        }
        Vec faceNormal = (edges[0] % edges[1]).normalize();

        // Test the triangle normal
        double triangleOffset = faceNormal | points[0];
        projectPointsOnAxis(points, faceNormal, boxMin, boxMax);
        if (boxMax < triangleOffset || boxMin > triangleOffset)
            return false; // No intersection possible.

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // The box normals are the same as it's edge tangents
                Vec axis = edges[i] % boxNormals[j];
                projectPointsOnAxis({bb.getMinBoundaries(), bb.getMaxBoundaries()}, axis, boxMin, boxMax);
                projectPointsOnAxis(points, axis, boxMin, boxMax);

                if (boxMax <= triangleMin || boxMin >= triangleMax)
                    return false; // No intersection possible
            }
        }

        // No separating axis found.
        return true;
    }

//    static bool faceIntersectsBoundingBox(BoundingBox bb, Mesh::FHandle f, Mesh &mesh) {
//        double triangleMin, triangleMax;
//        double boxMin, boxMax;
//
//        // Test the box normals (x-, y- and z-axes)
//        array<Vec, 3> boxNormals = {
//                Vec(1, 0, 0),
//                Vec(0, 1, 0),
//                Vec(0, 0, 1)
//        };
//        for (int i = 0; i < 3; i++) {
//            Vec n = boxNormals[i];
//            projectPointsOnAxis(f, boxNormals[i], triangleMin, triangleMax, mesh);
//            if (triangleMax < bb.getMinBoundaries()[i] || triangleMin > bb.getMaxBoundaries()[i])
//                return false; // No intersection possible.
//        }
//
//        Vec faceNormal = mesh.calc_face_normal(f);
//
//        // Test the triangle normal
//        double triangleOffset = faceNormal | mesh.point(*(mesh.fv_iter(f)));
//        projectPointsOnAxis({bb.getMinBoundaries(), bb.getMaxBoundaries()}, faceNormal, boxMin, boxMax);
//        if (boxMax < triangleOffset || boxMin > triangleOffset)
//            return false; // No intersection possible.
//
//
//        vector<Vec> triangleEdges;
//        for (Mesh::FaceEdgeIter it = mesh.fe_iter(f); it.is_valid(); it++) {
//            triangleEdges.push_back(mesh.calc_edge_vector(*it));
//        }
//        for (int i = 0; i < 3; i++)
//            for (int j = 0; j < 3; j++) {
//                // The box normals are the same as it's edge tangents
//                Vec axis = triangleEdges[i] % boxNormals[j];
//                projectPointsOnAxis({bb.getMinBoundaries(), bb.getMaxBoundaries()}, axis, boxMin, boxMax);
//                projectPointsOnAxis(f, axis, triangleMin, triangleMax, mesh);
//                if (boxMax <= triangleMin || boxMin >= triangleMax)
//                    return false; // No intersection possible
//            }
//
//        // No separating axis found.
//        return true;
//    }

//    static void projectPointsOnAxis(Mesh::FaceHandle f, Vec axis, double &min, double &max, Mesh &mesh) {
//        min = std::numeric_limits<double>::max();
//        max = std::numeric_limits<double>::min();
//        for (Mesh::FaceVertexIter it = mesh.fv_iter(f); it.is_valid(); it++) {
//            double val = axis | mesh.point(*it);
//            if (val < min) min = val;
//            if (val > max) max = val;
//        }
//    }
//
//    static void projectPointsOnAxis(const list<Vec> &points, Vec axis, double &min, double &max) {
//        min = std::numeric_limits<double>::max();
//        max = std::numeric_limits<double>::min();
//        for (Vec p : points) {
//            double val = axis | p;
//            if (val < min) min = val;
//            if (val > max) max = val;
//        }
//    }

    static void projectPointsOnAxis(const vector<Vec> &points, Vec axis, double &min, double &max) {
        min = std::numeric_limits<double>::max();
        max = std::numeric_limits<double>::lowest();
//        std::cout << "min: " << min << " max: " << max << std::endl;
        for (Vec p : points) {
            double val = axis | p;

//            std::cout << p << std::endl << val << std::endl << std::endl;
            if (val < min) min = val;
            if (val > max) max = val;
        }
    }

    static bool faceSphereIntersection(const vector<Vec> &face, const Vec &center, double radius) {

//        vector<Vec> edges = edgesFromPoints(face);
        Vec n = normalFromPoints(face);
        Vec H = projectPointOnPlane(center, n, face[0]);

        double d2 = (H - center).sqrnorm(), r2 = radius * radius;
//        std::cout << std::endl << "distance: " << d2 << " radius: " << r2;
        if (d2 > r2) {
            return false;
        }

        double t = coplanarPointToFaceDistance(H, face, n);
        return t * t <= r2 - d2;


    }

    static Vec projectPointOnPlane(const Vec &p, const Vec &planeNormal, const Vec &planePoint) {
        Vec v = ((p - planePoint) | planeNormal) * planeNormal;
        return p - v;
    }

    static double pointToSegmentDistance(const Vec &p, const Vec &a, const Vec &b) {
        Vec u = (b - a).normalize();

        double t = (p - a) | u, pmb = (p - a).sqrnorm() - t * t;
        if (t <= 0) {
            return (p - a).norm();
        }
        if (t >= (b - a).norm()) {
            return (p - b).norm();
        }


        return std::sqrt((p - a).sqrnorm() - t * t);
    }

    static double coplanarPointToFaceDistance(const Vec &p, const vector<Vec> &points, const Vec &normal) {
        if (isCoplanarPointInsideFace(p, points, normal)) {
            return 0;
        }

        double min = std::numeric_limits<double>::max(), d;
        for (int i = 0; i < points.size(); i++) {
            d = pointToSegmentDistance(p, points[(i + 1) % points.size()], points[i]);
            if (d < min) {
                min = d;
            }
        }
        return min;
    }

    static double coplanarPointToFaceDistance(const Vec &p, const vector<Vec> &points) {
        return coplanarPointToFaceDistance(p, points, normalFromPoints(points));
    }

    static bool isCoplanarPointInsideFace(const Vec &p, const vector<Vec> &points, const Vec &normal) {
        vector<double> nProducts(points.size());
        for (int i = 0; i < points.size(); i++) {
            nProducts[i] = ((p - points[i]) % (points[(i + 1) % points.size()] - points[i])) | normal;
        }

        int s = sign(nProducts[0]);
        for (int i = 1; i < nProducts.size(); i++) {
            if (sign(nProducts[i]) != s) {
                return false;
            }
        }

        return true;
    }

    static bool isCoplanarPointInsideFace(const Vec &p, const vector<Vec> &points) {
        return isCoplanarPointInsideFace(p, points, normalFromPoints(points));
    }


private:
    static vector<Vec> edgesFromPoints(const vector<Vec> points) {
        vector<Vec> edges(points.size());
        for (int i = 0; i < edges.size(); i++) {
            edges[i] = points[(i + 1) % edges.size()] - points[i];
        }
        return edges;
    }


    static Vec normalFromPoints(const vector<Vec> &points) {
        Vec v(0, 0, 0);
        for (int i = 0; v == Vec(0, 0, 0) && i < points.size() - 1; i++) {
            v = (points[(i + 2) % points.size()] - points[i + 1]) % (points[i + 1] - points[i]);
        }
        return v.normalize();
    }

    static int sign(double d) {
        return (d > 0) - (d < 0);
    }

};

#endif //SYMMETRY_DETECTION_TRIANGLE_BOX_H
