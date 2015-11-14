//
// Created by antoinewdg on 24/10/15.
//

#ifndef SYMMETRY_DETECTION_PLANE_H
#define SYMMETRY_DETECTION_PLANE_H

#include "common/common.h"

class Plane {
public:
    double r, theta, phi;


    Plane() { }

    Plane(double r, double theta, double phi) : r(r), theta(theta), phi(phi) {
        forceUniqueHorizontal();
    }

    static Plane betweenPoints(const Vec &p, const Vec &q) {
        Vec n = (p - q).normalize();
        Vec A = 0.5 * (p + q);

        return Plane::fromCartesian(n, A);
    }

    static Plane fromCartesian(const Vec &n, const Vec &point) {
        Vec H = projectPointOnCartesianPlane(Vec(0, 0, 0), n, point);
        std::cout << "H: " << H << " n: " << n << std::endl;
        Plane plane;
        plane.r = H.norm();
        if (plane.r > 0) {
            plane.phi = std::fmod(std::atan2(H[1], H[0]) + 2 * M_PI, 2 * M_PI);
            plane.theta = std::acos(H[2] / plane.r);
        } else {
            plane.phi = std::fmod(std::atan2(n[1], n[0]) + 2 * M_PI, 2 * M_PI);
            plane.theta = std::acos(n[2]);
        }
        std::cout << "atant: " << std::atan2(n[1], n[0]) << std::endl;
        std::cout << "thetha: " << plane.theta << " phi: " << plane.phi << std::endl;
        if (plane.theta > M_PI * 0.5) {
            plane.r = -plane.r;
            plane.theta = M_PI - plane.theta;
            plane.phi = std::fmod(plane.phi + M_PI, 2 * M_PI);
        }
        plane.forceUniqueHorizontal();
        return plane;
    }

    void forceUniqueHorizontal() {
        if (theta == 0) {
            phi = 0;
        }
    }


    static Vec projectPointOnCartesianPlane(const Vec &p, const Vec &planeNormal, const Vec &planePoint) {
        Vec v = ((p - planePoint) | planeNormal) * planeNormal;
        return p - v;
    }
};

#endif //SYMMETRY_DETECTION_PLANE_H
