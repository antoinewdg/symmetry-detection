//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_MESH_H
#define SYMMETRY_DETECTION_MESH_H

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

struct Traits : OpenMesh::DefaultTraits {
    typedef OpenMesh::Vec3d Point;
};

typedef OpenMesh::PolyMesh_ArrayKernelT<Traits> Mesh;
typedef OpenMesh::Vec3d Vec;
typedef OpenMesh::Vec3i Vec3i;

inline void displayFace(Mesh &mesh, Mesh::FaceHandle f) {
    for (Mesh::FaceVertexIter it = mesh.fv_iter(f); it.is_valid(); it++) {
        std::cout << mesh.point(*it) << " - ";
    }
}


#endif //SYMMETRY_DETECTION_MESH_H
