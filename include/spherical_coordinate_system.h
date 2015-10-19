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
    float radius;
    float rStep, thetaStep, phiStep;


public:
    void setRadius(float radius) {
        SphericalCoordinateSystem::radius = radius;
        rStep = 2 * radius / GRID_SIZE;
    }


    float getRadius() const {
        return radius;
    }

    float getRStep() const {
        return rStep;
    }

    float getThetaStep() const {
        return thetaStep;
    }

    float getPhiStep() const {
        return phiStep;
    }
};

#endif //SYMMETRY_DETECTION_SPHERICAL_COORDINATE_SYSTEM_H
