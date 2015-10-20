//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_SPHERICAL_COORDINATE_SYSTEM_H
#define SYMMETRY_DETECTION_SPHERICAL_COORDINATE_SYSTEM_H


#include <cmath>
#include "common/common.h"
#include "bounding_box.h"

class SphericalCoordinateSystem {
public:
    SphericalCoordinateSystem();

    SphericalCoordinateSystem(Mesh &mesh);


private:
    double radius;
    double rStep, thetaStep, phiStep;


public:
    void setRadius(double radius) {
        SphericalCoordinateSystem::radius = radius;
        rStep = 2 * radius / GRID_SIZE;
    }


    double getRadius() const {
        return radius;
    }

    double getRStep() const {
        return rStep;
    }

    double getThetaStep() const {
        return thetaStep;
    }

    double getPhiStep() const {
        return phiStep;
    }
};

#endif //SYMMETRY_DETECTION_SPHERICAL_COORDINATE_SYSTEM_H
