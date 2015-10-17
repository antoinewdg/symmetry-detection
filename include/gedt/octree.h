//
// Created by AntoineWDG on 10/16/15.
//

#ifndef SYMMETRY_DETECTION_OCTREE_H
#define SYMMETRY_DETECTION_OCTREE_H

#include <list>
#include <memory>
#include <bounding_box.h>

#include "common/common.h"


using std::list;
using std::shared_ptr;

class Node {

public:
    Node(shared_ptr<Mesh> mesh, const BoundingBox &boundingBox);

    shared_ptr<Node> parent;
    list<shared_ptr<Node>> children;

    list<Mesh::FaceHandle> faces;
    shared_ptr<Mesh> mesh;
    BoundingBox boundingBox;

    int depth = 0;

private:
    bool boxContainsFace(Mesh::FHandle f, const BoundingBox &bb);
};

#endif //SYMMETRY_DETECTION_OCTREE_H
