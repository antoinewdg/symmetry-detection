//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_MESH_FACTORY_H
#define SYMMETRY_DETECTION_MESH_FACTORY_H

#include "common/common.h"

class MeshFactory {
public:
    static Mesh basicCube(float u, float v, float w, float x, float y, float z) {
        Mesh mesh;
        Mesh::VertexHandle vhandle[8];

        vhandle[0] = mesh.add_vertex(Mesh::Point(u, v, w));
        vhandle[1] = mesh.add_vertex(Mesh::Point(u, v, z));
        vhandle[2] = mesh.add_vertex(Mesh::Point(u, y, w));
        vhandle[3] = mesh.add_vertex(Mesh::Point(u, y, z));
        vhandle[4] = mesh.add_vertex(Mesh::Point(x, v, w));
        vhandle[5] = mesh.add_vertex(Mesh::Point(x, v, z));
        vhandle[6] = mesh.add_vertex(Mesh::Point(x, y, w));
        vhandle[7] = mesh.add_vertex(Mesh::Point(x, y, z));


        // generate (quadrilateral) faces

        std::vector<Mesh::VertexHandle> face_vhandles;

        face_vhandles.clear();
        face_vhandles.push_back(vhandle[0]);
        face_vhandles.push_back(vhandle[1]);
        face_vhandles.push_back(vhandle[5]);
        face_vhandles.push_back(vhandle[4]);
        mesh.add_face(face_vhandles);

        face_vhandles.clear();
        face_vhandles.push_back(vhandle[1]);
        face_vhandles.push_back(vhandle[0]);
        face_vhandles.push_back(vhandle[2]);
        face_vhandles.push_back(vhandle[3]);
        mesh.add_face(face_vhandles);

        face_vhandles.clear();
        face_vhandles.push_back(vhandle[0]);
        face_vhandles.push_back(vhandle[4]);
        face_vhandles.push_back(vhandle[6]);
        face_vhandles.push_back(vhandle[2]);
        mesh.add_face(face_vhandles);

        face_vhandles.clear();
        face_vhandles.push_back(vhandle[3]);
        face_vhandles.push_back(vhandle[2]);
        face_vhandles.push_back(vhandle[6]);
        face_vhandles.push_back(vhandle[7]);
        mesh.add_face(face_vhandles);

        face_vhandles.clear();
        face_vhandles.push_back(vhandle[4]);
        face_vhandles.push_back(vhandle[5]);
        face_vhandles.push_back(vhandle[7]);
        face_vhandles.push_back(vhandle[6]);
        mesh.add_face(face_vhandles);
//
        face_vhandles.clear();
        face_vhandles.push_back(vhandle[5]);
        face_vhandles.push_back(vhandle[1]);
        face_vhandles.push_back(vhandle[3]);
        face_vhandles.push_back(vhandle[7]);
        mesh.add_face(face_vhandles);

        return mesh;
    }

//    static Mesh triangle(Vec a, Vec b, Vec c) {
//        Mesh mesh;
//        Mesh::VertexHandle vhandle[3];
//
//        vhandle[0] = mesh.add_vertex(a);
//        vhandle[1] = mesh.add_vertex(b);
//        vhandle[2] = mesh.add_vertex(c);
//
//        std::vector<Mesh::VertexHandle> face_vhandles;
//
//        face_vhandles.clear();
//        face_vhandles.push_back(vhandle[0]);
//        face_vhandles.push_back(vhandle[1]);
//        face_vhandles.push_back(vhandle[2]);
//        mesh.add_face(face_vhandles);
//
//    }
};

#endif //SYMMETRY_DETECTION_MESH_FACTORY_H
