//
// Created by antoinewdg on 11/10/15.
//

#ifndef SYMMETRY_DETECTION_GRID_H
#define SYMMETRY_DETECTION_GRID_H

#include "common/common.h"
#include "bounding_box.h"
#include "geometry/plane.h"

class Grid {
public:
    Grid(BoundingBox bb, int size) : bb(bb), size(size) {
        size2 = size * size;
        radius = (bb.getMax() - bb.getMin()).norm() / 2;
        rStep = 2 * radius / size;
        thetaStep = M_PI / (2 * size);
        phiStep = (2.0 / size) * M_PI;
    }

    Vec3i coordsFromPoint(const Vec &p) const {
        Vec3i r;
        Vec c(p);
//        std::cout << c << " - " << p << std::endl;
//        c = gridSize * (c - boundingBox.getMin());
        for (int i = 0; i < 3; i++) {
            c[i] = (double(size) / (bb.getMax()[i] - bb.getMin()[i])) *
                   (c[i] - bb.getMin()[i]);
            r[i] = int(std::floor(c[i]));
            if (r[i] >= size) {
                std::cout << "Error for float " << p[i] << std::endl;
            }
        }

        return r;
    }

    Vec voxelCenterFromCoords(const Vec3i &c) const {
        Vec r;

        for (int i = 0; i < 3; i++) {
            double ratio = (bb.getMax()[i] - bb.getMin()[i]) / size;
            r[i] = bb.getMin()[i] + ratio * (0.5 + c[i]);
        }

        return r;
    }

    double getVoxelVolume() const {

        return (bb.getMax()[0] - bb.getMin()[0])
               * (bb.getMax()[1] - bb.getMin()[1])
               * (bb.getMax()[2] - bb.getMin()[2])
               / (size * size2);
    }

    Plane closestDiscretePlane(Plane p) const {
        p.r = (std::round(((p.r + radius) / rStep) + 0.5) - 0.5) * rStep - radius;
        p.theta = (std::round((p.theta / thetaStep) + 0.5) - 0.5) * thetaStep;
        p.phi = (std::round((p.phi / phiStep) + 0.5) - 0.5) * phiStep;
//        p.forceUniqueHorizontal();

        return p;
    }

    BoundingBox bb;
    int size, size2;
    double radius, rStep, thetaStep, phiStep;
};

#endif //SYMMETRY_DETECTION_GRID_H
