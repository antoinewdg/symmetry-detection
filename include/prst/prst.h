//
// Created by antoinewdg on 11/11/15.
//

#ifndef SYMMETRY_DETECTION_PRST_H
#define SYMMETRY_DETECTION_PRST_H

#include <vector>

#include "common/common.h"
#include "gedt/gedt.h"
#include "geometry/grid.h"
#include "geometry/plane.h"
#include "prst/sampler.h"

using std::vector;

class PRST {
public:
    PRST(const GEDT &f);

private:
    const Grid &grid;
    const GEDT &f;
    Sampler sampler;
};

#endif //SYMMETRY_DETECTION_PRST_H
