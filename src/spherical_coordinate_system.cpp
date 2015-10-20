#include "spherical_coordinate_system.h"


SphericalCoordinateSystem::SphericalCoordinateSystem() {
    phiStep = M_PI / (2 * GRID_SIZE);
    thetaStep = 2 * M_PI / GRID_SIZE;
}

SphericalCoordinateSystem::SphericalCoordinateSystem(Mesh &mesh) : SphericalCoordinateSystem() {
    BoundingBox::centerMeshVertices(mesh);
    BoundingBox bb(mesh);
    setRadius(bb.getMaxBoundaries().norm());

}



