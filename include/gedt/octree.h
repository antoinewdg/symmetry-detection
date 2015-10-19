//
// Created by AntoineWDG on 10/16/15.
//

#ifndef SYMMETRY_DETECTION_OCTREE_H
#define SYMMETRY_DETECTION_OCTREE_H

#include <cmath>
#include <list>
#include <vector>
#include <memory>
#include <bounding_box.h>

#include "common/common.h"
#include "geometry/face_intersection.h"


using std::list;
using std::shared_ptr;
using std::weak_ptr;
using std::vector;

class OCTree {


    class Node {

    public:

        Node(OCTree *tree, Mesh &mesh, const BoundingBox &boundingBox, const list<Mesh::FaceHandle> &potentialFaces,
             int maxDepth = OCTREE_DEPTH, int depth = 0, Node *parent = nullptr);

//        Node(OCTree *tree, Mesh &mesh, const BoundingBox &boundingBox, const list<Mesh::FaceHandle> &potentialFaces,
//             int maxDepth, int depth, Node *parent);

        virtual ~Node();

        Node *parent;
        list<Node *> children;

        Mesh &mesh;
        BoundingBox boundingBox;
        long facesNumber;
        int depth;

    private:
        bool boxContainsFace(Mesh::FHandle f, const BoundingBox &bb);

    };

public:
    OCTree(Mesh &mesh, const BoundingBox &boundingBox, const list<Mesh::FaceHandle> &potentialFaces,
           int maxDepth = OCTREE_DEPTH);

    virtual ~OCTree();

    Vec3i gridCoordsFromPoint(Vec p) const {
        Vec3i r;
        p = (p - boundingBox.getMinBoundaries()) * gridSize;
        for (int i = 0; i < 3; i++) {
            p[i] /= boundingBox.getMaxBoundaries()[i];
            r[i] = int(std::floor(p[i]));
        }

        return r;
    }

private:
    Node *root;
    BoundingBox boundingBox;
    int gridSize, gridSize2;
    vector<int> voxelValues;

    inline void setVoxelValue(const Vec3i &c, int v) {
        voxelValues[c[0] * gridSize2 + c[1] * gridSize + c[2]] = v;
    }

    inline void setVoxelValue(const Vec &p, int v) {
        setVoxelValue(gridCoordsFromPoint(p), v);
    }

public:

    inline int getVoxelValue(int a, int b, int c) const {
        return voxelValues[a * gridSize2 + b * gridSize + c];
    }

    inline int getVoxelValue(const Vec3i &c) const {
        return getVoxelValue(c[0], c[1], c[2]);
    }

    inline int getVoxelValue(const Vec &p) const {
        return getVoxelValue(gridCoordsFromPoint(p));
    }


};


#endif //SYMMETRY_DETECTION_OCTREE_H
