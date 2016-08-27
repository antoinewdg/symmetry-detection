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

    void computeMaxima(GEDT gedt) {
        Grid grid = gedt.getGrid();

        /* Calculate PRST of all plans (discrete ones we have) */
        double max = 0;
        double PRST;
        for (double r = -grid.radius; r<grid.radius; r += grid.rStep){
            for (double theta = 0; theta < M_PI; theta += grid.thetaStep){
                for (double phi = 0; phi <2* M_PI; phi += grid.phiStep){
                    Plane plane (r, theta, phi);
                    // on regarde le plan discret le plus proche (potentiellement confondu avec plane ?)
                    plane = grid.closestDiscretePlane(plane);
                    //on calcule sa PRST
                    PRST = PRST(plane);
                    //on regarde si c'est un max local
                    bool isMaxima = true;
                    vector<Plane> neighbors = plane.neighbors(grid);
                    for (int i=0; i<neighbors.size(); i++) {
                        if (PRST(neighbors[i]) > PRST) {
                            isMaxima = false;
                            break;
                        }
                    }
                    //Si c'est un max local, on vérifie si c'est le max global,
                    // et dans ce cas on le conserve
                    if (isMaxima && PRST > max) {
                        max = PRST;
                    }
                }
            }
        }

        threshold = 1 / 10 * max;

        /* Get rid of points under threshold*(1-r/R) with r : distance of the plane to the center of mass
         * (compute center of mass later)
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
