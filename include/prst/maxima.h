//
// Created by geoffrey on 10/11/15.
//

#ifndef SYMMETRY_DETECTION_MAXIMA_H
#define SYMMETRY_DETECTION_MAXIMA_H

#include <opencv2/core/types_c.h>
#include "geometry/plane.h"

using std::vector

class Maxima {
public:
    vector<CvPoint> PRSTMaxima;
    double threshold;

    void computeMaxima() {

        /* Calculate PRST of all plans (discrete ones we have) */
        double max = 0;
        double PRST;
        for (double r = 0; r<rMax; r += rStep){
            for (double theta = 0; theta < M_PI; theta += thetaStep){
                for (double phi = 0; phi <2* M_PI; phi += phiStep){
                    Plane plane (r, theta, phi);
                    PRST = PRST(plane);
                    if (PRST > max) {
                        max = PRST;
                    }
                    bool isMaxima = true;
                    vector<Plane> neighbors = plane.neighbors(rStep, thetaStep, phiStep);
                    for (int i=0; i<neighbors.size(); i++) {
                        if (PRST(neighbors[i]) > PRST) {
                            isMaxima = false;
                            break;
                        }
                    }
                }
            }
        }

        this.threshold = 1 / 10 * max;

        /* threshold = 1/10*max of local maxima
        * Get rid of points under threshold*(1-r/R) with r : distance of the plane to the center of mass
        * R : radius of the object
        * Then, we get rid of those whose Laplacian is under threshold
        *
        * Refinement: ISP algorithm
        *iterate : */
        for (int i = 0; i< 50; i++) {

            /* Find sample points (~10k) ON THE MESH */
            Vec3d samplePoint;
            /* Reflect them on candidate plane*/

            /* Match to closest point on the mesh
            * Solve for the plane that minimizes sum of distances weighted by GEDT between corresponding points
            * (minimal sum of weighted distances provides a maximum for Equation 2 when f is the GEDT of the surface)
            * iterate until convergence
            */
        }
    }
};

#endif //SYMMETRY_DETECTION_MAXIMA_H
