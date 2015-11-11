#include <iostream>
#include <array>
#include <random>
//#include <factory/mesh_factory.h>

#include "common/common.h"
#include "bounding_box.h"
#include "spherical_coordinate_system.h"
#include "gedt/octree.h"
#include "gedt/gedt.h"

using std::array;
using std::list;

int main() {

    Mesh mesh;
    if (!OpenMesh::IO::read_mesh(mesh, ASSETS_DIR "/teapot.off")) {
        std::cerr << "read error\n";
        exit(1);
    }
//
//    BoundingBox::centerMeshVertices(mesh);
//    BoundingBox d(mesh);
////    std::cout << d.getCenter() << std::endl;
//
    list<Mesh::FaceHandle> faces;
    std::copy(mesh.faces_begin(), mesh.faces_end(), std::back_inserter(faces));

    GEDT gedt(mesh, OCTREE_DEPTH);
//    std::cout << std::endl << gedt.getPointsOfInterest().size();
//    vector<double> v(64 * 64 * 64, 1.0);
//
//    std::discrete_distribution<int> distribution(v.begin(), v.end());
//
//    std::default_random_engine generator;
//
//    for (int i = 0; i < 10000; i++) {
//        std::cout << distribution(generator) << std::endl;
//    }
//    OCTree tree(mesh, d, faces, 7);
//    int r = 128;
//    for (int x = 0; x < r; x++) {
//        for (int y = 0; y < r; y++) {
//            if (tree.getVoxelValue(x, y, r / 2) > 0) {
//                std::cout << " ";
//            } else {
//                std::cout << 0;
//            }
////            std::cout << ;
//        }
//        std::cout << std::endl;
//    }
//
//    if (!OpenMesh::IO::write_mesh(MeshFactory::basicCube(0, 0, 0, 1, 1, 1), ASSETS_DIR "/out.ply")) {
//        std::cerr << "write error\n";
//        exit(1);
//    }

//    Node n(std::make_shared<Mesh>(mesh), d);
//    for (Mesh::VertexIter it = mesh.vertices_begin(); it != mesh.vertices_end(); it++) {
//        p = mesh.point(*it);
//        for (Mesh::VertexIter jt = mesh.vertices_begin(); jt != mesh.vertices_end(); jt++) {
//            q = mesh.point(*jt);
//        }
//    }


    return 0;
}