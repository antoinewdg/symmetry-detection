//
// Created by geoffrey on 11/11/15.
//

#ifndef SYMMETRY_DETECTION_CARTESIANPLANE_H
#define SYMMETRY_DETECTION_CARTESIANPLANE_H

#include "geometry/plane.h"
#include "sphericalplane.h"

class CartesianPlane : public Plane{
public:
    Vec normal, point;

    CartesianPlane() : Plane{ }

    CartesianPlane(Vec normal, Vec point) : Plane(), normal(normal), point(point) { }

    CartesianPlane(SphericalPlane sPlane): Plane() {
    }

    Vec projectPoint(const Vec &p) const {
        Vec v = ((p - point) | normal) * normal;
        return p - v;
    }

    static Vec reflectPointOnCartesianPlane(const Vec &p, const Vec &planeNormal, const Vec &planePoint){
        Vec v = projectPointOnCartesianPlane(p, planeNormal, planePoint);
        return 2*v-p;
    }


};

#endif //SYMMETRY_DETECTION_CARTESIANPLANE_H
