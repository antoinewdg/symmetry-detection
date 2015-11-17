//
// Created by geoffrey on 11/11/15.
//

#ifndef SYMMETRY_DETECTION_SPHERICALPLANE_H
#define SYMMETRY_DETECTION_SPHERICALPLANE_H

#include "geometry/plane.h"
#include "common/common.h"

using std::vector
using std::pair

class SphericalPlane : public Plane{

    public:
        double r, theta, phi;

        SphericalPlane() : Plane() { }

        SphericalPlane(double r, double theta, double phi) : r(r), theta(theta), phi(phi) { }

        vector<Plane> neighbors(double rStep, double thetaStep, double phiStep){
            vector<Plane> result;
            result.push_back(Plane(r+rStep, theta, phi));
            result.push_back(Plane(r+rStep, theta+thetaStep, phi));
            result.push_back(Plane(r+rStep, theta-thetaStep, phi));
            result.push_back(Plane(r+rStep, theta, phi+phiStep));
            result.push_back(Plane(r+rStep, theta, phi-phiStep));
            result.push_back(Plane(r+rStep, theta+thetaStep, phi+phiStep));
            result.push_back(Plane(r+rStep, theta+thetaStep, phi-phiStep));
            result.push_back(Plane(r+rStep, theta-thetaStep, phi+phiStep));
            result.push_back(Plane(r+rStep, theta-thetaStep, phi-phiStep));

            result.push_back(Plane(r-rStep, theta, phi));
            result.push_back(Plane(r-rStep, theta+thetaStep, phi));
            result.push_back(Plane(r-rStep, theta-thetaStep, phi));
            result.push_back(Plane(r-rStep, theta, phi+phiStep));
            result.push_back(Plane(r-rStep, theta, phi-phiStep));
            result.push_back(Plane(r-rStep, theta+thetaStep, phi+phiStep));
            result.push_back(Plane(r-rStep, theta+thetaStep, phi-phiStep));
            result.push_back(Plane(r-rStep, theta-thetaStep, phi+phiStep));
            result.push_back(Plane(r-rStep, theta-thetaStep, phi-phiStep));

            result.push_back(Plane(r, theta+thetaStep, phi));
            result.push_back(Plane(r, theta-thetaStep, phi));
            result.push_back(Plane(r, theta, phi+phiStep));
            result.push_back(Plane(r, theta, phi-phiStep));
            result.push_back(Plane(r, theta+thetaStep, phi+phiStep));
            result.push_back(Plane(r, theta+thetaStep, phi-phiStep));
            result.push_back(Plane(r, theta-thetaStep, phi+phiStep));
            result.push_back(Plane(r, theta-thetaStep, phi-phiStep));

            return result;
        }

        static Plane betweenPoints(const Vec &p, const Vec &q) {
            Vec n = (p - q).normalize();
            Vec A = 0.5 * (p + q);
            return Plane::fromCartesian(n, A);
        }

        static Plane fromCartesian(const Vec &normal, const Vec &point) {
            Vec H = projectPointOnCartesianPlane(Vec(0, 0, 0), normal, point);
            Plane plane;
            plane.r = H.norm();
            plane.phi = std::atan2(H[1], H[0]);
            plane.theta = std::acos(H[2] / plane.r);
            if (plane.theta > M_PI * 0.5) {
                plane.r = -plane.r;
                plane.theta = M_PI - plane.theta;
                plane.phi = std::fmod(plane.phi + M_PI, 2 * M_PI);
            }

            return plane;
        }



        static Vec projectPointOnCartesianPlane(const Vec &p, const Vec &planeNormal, const Vec &planePoint) {
            Vec v = ((p - planePoint) | planeNormal) * planeNormal;
            return p - v;
        }

        static Vec reflectPointOnCartesianPlane(const Vec &p, const Vec &planeNormal, const Vec &planePoint){
            Vec v = projectPointOnCartesianPlane(p, planeNormal, planePoint);
            return 2*v-p;
        }

};

#endif //SYMMETRY_DETECTION_SPHERICALPLANE_H