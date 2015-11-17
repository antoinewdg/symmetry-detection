//
// Created by antoinewdg on 11/15/15.
//

#ifndef SYMMETRY_DETECTION_GEDT_FACTORY_H
#define SYMMETRY_DETECTION_GEDT_FACTORY_H

#include "common/common.h"
#include "gedt/gedt.h"
#include "factory/mesh_factory.h"

class GEDTFactory {
public:
    static GEDT basicCube(double u, double v, double w, double x, double y, double z) {
        Mesh mesh = MeshFactory::basicCube(u, v, w, x, y, z);
        return GEDT(mesh, 4);
    }
};

#endif //SYMMETRY_DETECTION_GEDT_FACTORY_H
