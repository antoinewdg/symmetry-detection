#include "spherical_coordinate_system.h"


SphericalCoordinateSystem::SphericalCoordinateSystem() {
    phiStep = float(M_PI / (2 * GRID_SIZE));
    thetaStep = float(2 * M_PI / GRID_SIZE);
}

SphericalCoordinateSystem::SphericalCoordinateSystem(Mesh &mesh) : SphericalCoordinateSystem() {
    centerMeshVertices(mesh);
    BoundingBox bb(mesh);
    setRadius(bb.getMaxBoundaries().norm());

}

void SphericalCoordinateSystem::centerMeshVertices(Mesh &mesh) {
    BoundingBox bb(mesh);
    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
        mesh.point(*it) = mesh.point(*it) - bb.getCenter();
    }

}

