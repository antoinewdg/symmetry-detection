#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <array>

#include "common/common.h"
#include "bounding_box.h"
#include "spherical_coordinate_system.h"


using std::array;

int main() {

    Mesh mesh;
    if (!OpenMesh::IO::read_mesh(mesh, ASSETS_DIR "/bun_zipper.ply")) {
        std::cerr << "read error\n";
        exit(1);
    }

    SphericalCoordinateSystem::centerMeshVertices(mesh);
    BoundingBox d(mesh);
    std::cout << d.getCenter() << std::endl;

    if (!OpenMesh::IO::write_mesh(mesh, ASSETS_DIR "/out.ply")) {
        std::cerr << "write error\n";
        exit(1);
    }
//    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
//        p = mesh.point(*it);
//        for (Mesh::VertexIter jt = mesh.vertices_begin(); jt != mesh.vertices_end(); jt++) {
//            q = mesh.point(*jt);
//        }
//    }


    return 0;
}