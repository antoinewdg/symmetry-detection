//
// Created by AntoineWDG on 10/14/15.
//

#include "bounding_box.h"

BoundingBox::BoundingBox(const Mesh &mesh) {

    evaluateBoundaries(mesh);
}


BoundingBox::BoundingBox(Vec minBoundaires, Vec maxBoundaries) :
        minBoundaries(minBoundaires), maxBoundaries(maxBoundaries) {
    center = 0.5f * (minBoundaries + maxBoundaries);
}

void BoundingBox::evaluateBoundaries(const Mesh &mesh) {

    maxBoundaries = mesh.point(*mesh.vertices_begin()), minBoundaries = maxBoundaries;

    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
        Vec p = mesh.point(*it);
        for (int i = 0; i < p.size(); i++) {
            if (p[i] < minBoundaries[i]) {
                minBoundaries[i] = p[i];
            }
            if (p[i] > maxBoundaries[i]) {
                maxBoundaries[i] = p[i];
            }

        }
    }

    Vec delta = (1.0 / 10) * (maxBoundaries - minBoundaries);
    minBoundaries -= delta;
    maxBoundaries += delta;

    center = 0.5f * (minBoundaries + maxBoundaries);

}

void BoundingBox::centerMeshVertices(Mesh &mesh) {
    BoundingBox bb(mesh);
    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
        mesh.point(*it) = mesh.point(*it) - bb.getCenter();
    }

}