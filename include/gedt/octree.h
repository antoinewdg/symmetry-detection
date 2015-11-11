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
#include "geometry/grid.h"
#include "util/tensor.h"


using std::list;
using std::unique_ptr;
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
    OCTree(Mesh &mesh, const BoundingBox &boundingBox, int maxDepth);

    void computeMesh(const list<Mesh::FaceHandle> &potentialFaces);


private:
    unique_ptr<Node> root;
    Grid grid;
    Mesh &mesh;
    int maxDepth;
    Tensori voxelValues;


public:

    inline int getVoxelValue(int a, int b, int c) const {
        return voxelValues(a, b, c);
    }

    inline int getVoxelValue(const Vec3i &c) const {
        return getVoxelValue(c[0], c[1], c[2]);
    }

    inline int getVoxelValue(const Vec &p) const {
        return getVoxelValue(grid.coordsFromPoint(p));
    }

    inline const Grid &getGrid() const {
        return grid;
    }
};


#endif //SYMMETRY_DETECTION_OCTREE_H
