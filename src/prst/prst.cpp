#include "prst/prst.h"


PRST::PRST(const GEDT &f) :
        f(f), grid(f.getGrid()), sampler(f), values(grid.size3, 0), counts(grid.size3, 0), max(0) {

    vector<Vec> samplesA(sampler.samples(2 * grid.size2)),
            samplesB(sampler.samples(2 * grid.size2));

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

    Mesh::VertexHandle vhandle[8];

    Vec n, point;
    maxP.toCartesian(n, point);


    vhandle[0] = f.getMesh().add_vertex(point + 3 * grid.radius * Vec(-n[1], n[0], 0));
    vhandle[1] = f.getMesh().add_vertex(point + 3 * grid.radius * Vec(0, -n[2], n[1]));
    vhandle[2] = f.getMesh().add_vertex(point + 3 * grid.radius * Vec(n[2], 0, -n[0]));

    f.getMesh().add_face({vhandle[0], vhandle[1], vhandle[2]});

    if (!OpenMesh::IO::write_mesh(f.getMesh(), ASSETS_DIR "/out.ply")) {
        std::cerr << "write error\n";
        exit(1);
    }
//    std::cout << grid.bb << std::endl << grid << std::endl;

//    std::cout << grid.size3 << std::endl;
//    for (int i = 0; i < grid.size3; i++) {
//        if (counts[i] > 0) {
//            values[i] /= counts[i];
//        }
//    }
//    double max = 0;
//    for (int i = 0; i < grid.size3; i++) {
//        if (values[i] > -1) {
//            std::cout << values[i] / (2 * grid.size2 * 2 * grid.size2) << " ";
//            if (i % 50 == 0) {
//                std::cout << std::endl;
//            }
//        }
//    }

    std::cout << std::endl << maxP << std::endl << max << std::endl;
    counts.resize(0);
}