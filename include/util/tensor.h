//
// Created by antoinewdg on 20/10/15.
//

#ifndef SYMMETRY_DETECTION_TENSOR_H
#define SYMMETRY_DETECTION_TENSOR_H

#include <vector>
#include "common/common.h"

using std::vector;

template<typename T>
class Tensor {
public:

    Tensor() { }

    Tensor(int xSize, int ySize, int zSize) : data(xSize * ySize * zSize), xSize(xSize), ySize(ySize), zSize(zSize) {

    }

    Tensor(int xSize, int ySize, int zSize, T v) : data(xSize * ySize * zSize, v), xSize(xSize), ySize(ySize),
                                                   zSize(zSize) {

    }

    T &operator()(int x, int y, int z) {
        return data[x * ySize * zSize + y * zSize + z];
    }

    T &operator()(Vec3i c) {
        return (*this)(c[0], c[1], c[2]);
    }

    T operator()(int x, int y, int z) const {
        return data[x * ySize * zSize + y * zSize + z];
    }

    T operator()(Vec3i c) const {
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
    vector<T> data;
    int xSize, ySize, zSize;

public:
    const vector<double> &getData() const {
        return data;
    }

    vector<double> &getData() {
        return data;
    }
};


typedef Tensor<double> Tensord;
typedef Tensor<int> Tensori;

#endif //SYMMETRY_DETECTION_TENSOR_H
