//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_REPARTITION_H
#define SYMMETRY_DETECTION_REPARTITION_H


#include "common/common.h"


class BoundingBox {

public:

    BoundingBox(const Mesh &mesh);


private:
    void evaluateBoundaries(const Mesh &mesh);


private:
    Point minBoundaries, maxBoundaries;
    Point center;

public:
    const Point &getMinBoundaries() const {
        return minBoundaries;
    }

    const Point &getMaxBoundaries() const {
        return maxBoundaries;
    }

    const Point &getCenter() const {
        return center;
    }
};


#endif //SYMMETRY_DETECTION_REPARTITION_H
