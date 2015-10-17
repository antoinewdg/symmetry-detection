#include "gedt/octree.h"

Node::Node(shared_ptr<Mesh> mesh, const BoundingBox &boundingBox) :
        mesh(mesh), boundingBox(boundingBox), parent(nullptr) {

    std::cout << mesh->calc_face_normal(*(mesh->faces_begin())) << std::endl;
}


bool Node::boxContainsFace(Mesh::FHandle f, const BoundingBox &bb) {
    float r = (bb.getMaxBoundaries() - bb.getCenter()).norm();
    
    return false;
}
