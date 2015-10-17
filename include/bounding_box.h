//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_REPARTITION_H
#define SYMMETRY_DETECTION_REPARTITION_H


#include "common/common.h"


class BoundingBox {

public:

    BoundingBox(const Mesh &mesh);

    BoundingBox(Vec minBoundaires, Vec maxBoundaries);


private:
    void evaluateBoundaries(const Mesh &mesh);


private:
    Vec minBoundaries, maxBoundaries;
    Vec center;

public:
    const Vec &getMinBoundaries() const {
        return minBoundaries;
    }

    const Vec &getMaxBoundaries() const {
        return maxBoundaries;
    }

    const Vec &getCenter() const {
        return center;
    }
};


#endif //SYMMETRY_DETECTION_REPARTITION_H
