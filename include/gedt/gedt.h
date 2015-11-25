//
// Created by antoinewdg on 19/10/15.
//

#ifndef SYMMETRY_DETECTION_GEDT_H
#define SYMMETRY_DETECTION_GEDT_H


#include <utility>

#include <bounding_box.h>
#include "common/common.h"
#include "octree.h"
#include "util/tensor.h"
#include "geometry/grid.h"

#define GEDT_SIGMA2 1.73
#define GEDT_MAXD 4


class GEDT {
public:
    GEDT(Mesh &mesh, int treeDepth);


    inline double operator()(const Vec &p) const {
        return values(grid.coordsFromPoint(p));
    }

    inline double operator()(const Vec3i &c) const {
        return values(c);
    }

private:
    Mesh &mesh;
    BoundingBox boundingBox;

    Tensord values;
    OCTree tree;
    const Grid &grid;
    list<Vec3i> seeds;
    double norm;


    static Vec3i immediateNeighbor(int i) {
        return Vec3i((i < 2) * (2 * i - 1), (i >= 2) * (i < 4) * (2 * i - 5), (i >= 4) * (2 * i - 9));
    }

    void regionGrowth(const Vec3i &c, const Vec3i &seed, double maxD2, double sigma2);

    void initializeSeeds();

    bool areCoordsInGrid(Vec3i c) {
        return c[0] >= 0 && c[0] < grid.size &&
               c[1] >= 0 && c[1] < grid.size &&
               c[2] >= 0 && c[2] < grid.size;
    }

public:

    const Tensord &getValues() const {
        return values;
    }

    Mesh &getMesh() const {
        return mesh;
    }

    const OCTree &getTree() const {
        return tree;
    }

    const Grid &getGrid() const {
        return grid;
    }
};

#endif //SYMMETRY_DETECTION_GEDT_H
