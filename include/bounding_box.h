//
// Created by AntoineWDG on 10/14/15.
//

#ifndef SYMMETRY_DETECTION_REPARTITION_H
#define SYMMETRY_DETECTION_REPARTITION_H

#include <vector>
#include "common/common.h"

using std::vector;

class BoundingBox {

public:

    BoundingBox() { }

    BoundingBox(const Mesh &mesh);

    BoundingBox(Vec minBoundaires, Vec maxBoundaries);

    vector<BoundingBox> subdivisions() const {
        vector<BoundingBox> subdivisions;
        Vec delta;
        subdivisions.push_back(BoundingBox(minBoundaries, center));
//        std::cout << "min : " << subdivisions[0].getMin() << " max: " <<
//        subdivisions[0].getMax() << std::endl;
        for (int i = 0; i < 3; i++) {
            delta = Vec(0, 0, 0);
            delta[i] = center[i] - minBoundaries[i];
            subdivisions.push_back(BoundingBox(minBoundaries + delta, center + delta));
//            std::cout << "min : " << subdivisions[i + 1].getMin() << " max: " <<
//            subdivisions[i + 1].getMax() << std::endl;
        }
        for (int i = 0; i < 3; i++) {
            delta = Vec(0, 0, 0);
            delta[(i + 1) % 3] = center[(i + 1) % 3] - minBoundaries[(i + 1) % 3];
            delta[(i + 2) % 3] = center[(i + 2) % 3] - minBoundaries[(i + 2) % 3];
            subdivisions.push_back(BoundingBox(minBoundaries + delta, center + delta));
        }
        subdivisions.push_back(BoundingBox(center, maxBoundaries));

        return subdivisions;
    }

    static void centerMeshVertices(Mesh &mesh);

private:
    void evaluateBoundaries(const Mesh &mesh);


private:
    Vec minBoundaries, maxBoundaries;
    Vec center;

public:
    const Vec &getMin() const {
        return minBoundaries;
    }

    const Vec &getMax() const {
        return maxBoundaries;
    }

    const Vec &getCenter() const {
        return center;
    }
};

inline std::ostream &operator<<(std::ostream &out, const BoundingBox &bb) {
    out << "[" << bb.getMin() <<
    " - " << bb.getCenter() <<
    " - " << bb.getMax() << "]";
    return out;
}

#endif //SYMMETRY_DETECTION_REPARTITION_H
