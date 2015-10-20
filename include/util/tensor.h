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

    static Tensor createGaussianKernel(int halfwidth, double sigma2) {
        Tensor kernel(2 * halfwidth + 1, 2 * halfwidth + 1, 2 * halfwidth + 1);
        for (int u = -halfwidth; u <= halfwidth; u++) {
            for (int v = -halfwidth; v <= halfwidth; v++) {
                for (int w = -halfwidth; w <= halfwidth; w++) {
                    kernel(u + halfwidth, v + halfwidth, w + halfwidth) = std::exp(
                            -(u * u + v * v + w * w) / sigma2
                    );
                }
            }
        }

        return kernel;
    }

private:
    vector<double> data;
    int xSize, ySize, zSize;
};

#endif //SYMMETRY_DETECTION_TENSOR_H
