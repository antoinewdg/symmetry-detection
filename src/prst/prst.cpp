#include "prst/prst.h"


PRST::PRST(const GEDT &f) :
        f(f), grid(f.getGrid()), sampler(f), values(grid.size3, 0), counts(grid.size3, 0), max(0) {

    vector<Vec> samplesA(sampler.samples(grid.size2)),
            samplesB(sampler.samples(grid.size2));

//    Plane

    for (Vec &x : samplesA) {
        for (Vec &y : samplesB) {
            if (x == y) { continue; }
            Plane p = grid.closestDiscretePlane(Plane::betweenPoints(x, y));

            int i = grid.planeIndex(p);
//            std::cout << x << "  --  " << y << std::endl;
//            if (i < 0 || i >= grid.size3) {
//                std::cout << Plane::betweenPoints(x, y) << " __ " << x << " - " << y << " = " << (x + y) / 2 <<
//                std::endl;
////                std::cout << Plane::betweenPoints(x, y) << " __ " << p << std::endl;
//            }
            values[i] += 1 / (2 * (x - y).sqrnorm() * std::sin(p.theta));
            if (max < values[i]) {
                max = values[i];
                maxP = p;
            }
            counts[i]++;
        }
    }

    /* TODO Move somewhere else */
//
    Mesh::VertexHandle vhandle[4];
////
//    Vec n, point;
//    std::cout << maxP << std::endl << std::endl;
//    maxP.toCartesian(n, point);
//    std::cout << "n:" << n << " p:" << point << std::endl;
//    Vec A = grid.bb.getMin(),
//            B = grid.bb.getMax(),
//            C = Vec(grid.bb.getMax()[0], grid.bb.getMin()[1], grid.bb.getMin()[2]),
//            D = Vec(grid.bb.getMin()[0], grid.bb.getMax()[1], grid.bb.getMax()[2]);
////
//    vhandle[0] = f.getMesh().add_vertex(Mesh::Point(0, 0, 0));//Plane::projectPointOnCartesianPlane(A, n, point));
//    vhandle[1] = f.getMesh().add_vertex(Plane::projectPointOnCartesianPlane(B, n, point));
//    vhandle[2] = f.getMesh().add_vertex(Plane::projectPointOnCartesianPlane(C, n, point));
//    vhandle[3] = f.getMesh().add_vertex(Plane::projectPointOnCartesianPlane(D, n, point));
//
//
//    f.getMesh().add_face({vhandle[0], vhandle[1], vhandle[2]});
//    f.getMesh().add_face({vhandle[1], vhandle[0], vhandle[3]});
//
//    if (!OpenMesh::IO::write_mesh(f.getMesh(), ASSETS_DIR "/out.ply")) {
//        std::cerr << "write error\n";
//        exit(1);
//    }


//    std::cout << std::endl << maxP << std::endl << max << std::endl;
    counts.resize(0);
}