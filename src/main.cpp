#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <array>
#include <mesh_factory.h>

#include "common/common.h"
#include "bounding_box.h"
#include "spherical_coordinate_system.h"
#include "gedt/octree.h"

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

    if (!OpenMesh::IO::write_mesh(MeshFactory::basicCube(0, 0, 0, 1, 1, 1), ASSETS_DIR "/out.ply")) {
        std::cerr << "write error\n";
        exit(1);
    }

//    Node n(std::make_shared<Mesh>(mesh), d);
//    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
//        p = mesh.point(*it);
//        for (Mesh::VertexIter jt = mesh.vertices_begin(); jt != mesh.vertices_end(); jt++) {
//            q = mesh.point(*jt);
//        }
//    }


    return 0;
}