//
// Created by AntoineWDG on 10/16/15.
//

#ifndef SYMMETRY_DETECTION_TRIANGLE_BOX_H
#define SYMMETRY_DETECTION_TRIANGLE_BOX_H

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


};

#endif //SYMMETRY_DETECTION_TRIANGLE_BOX_H
