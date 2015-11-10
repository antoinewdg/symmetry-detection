//
// Created by antoinewdg on 20/10/15.
//

#ifndef SYMMETRY_DETECTION_TENSOR_H
#define SYMMETRY_DETECTION_TENSOR_H

#include <vector>
#include "common/common.h"

using std::vector;

class Tensor {
public:
    Tensor(int xSize, int ySize, int zSize) : data(xSize * ySize * zSize), xSize(xSize), ySize(ySize), zSize(zSize) {

    }

    Tensor(int xSize, int ySize, int zSize, double v) : data(xSize * ySize * zSize, v), xSize(xSize), ySize(ySize),
                                                        zSize(zSize) {

    }

    double &operator()(int x, int y, int z) {
        return data[x * ySize * zSize + y * zSize + z];
    }

    double &operator()(Vec3i c) {
        return (*this)(c[0], c[1], c[2]);
    }

    double operator()(int x, int y, int z) const {
        return data[x * ySize * zSize + y * zSize + z];
    }

    double operator()(Vec3i c) const {
        return (*this)(c[0], c[1], c[2]);
    }

    Vec3i coordsFromIndex(int i) const {
        Vec3i c;
        c[2] = i % zSize;
        i /= zSize;
        c[1] = i % ySize;
        c[0] = i / ySize;
        return c;
    }

private:
    vector<double> data;
    int xSize, ySize, zSize;

public:
    const vector<double> &getData() const {
        return data;
    }

    vector<double> &getData() {
        return data;
    }
};

#endif //SYMMETRY_DETECTION_TENSOR_H
