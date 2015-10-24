//
// Created by antoinewdg on 24/10/15.
//

#ifndef SYMMETRY_DETECTION_SAMPLER_H
#define SYMMETRY_DETECTION_SAMPLER_H

#include <random>
#include <chrono>
#include <vector>

#include "common/common.h"
#include "gedt/gedt.h"

using std::vector;

class Sampler {
public:
    Sampler(const GEDT &f) : f(f), tree(f.getTree()) {
        unsigned int seed = unsigned(std::chrono::system_clock::now().time_since_epoch().count());
        generator.seed(seed);
        distribution = std::discrete_distribution<int>(f.getValues().getData().begin(), f.getValues().getData().end());
    }

    Vec next() {
        Vec3i c = f.getValues().coordsFromIndex(distribution(generator));
//        std::cout << "sampled: " << c << std::endl;
        return tree.voxelCenterFromCoords(c);
    }

    vector<Vec> samples(unsigned int n) {
        vector<Vec> s(n);
        for (int i = 0; i < n; i++) {
            s[i] = next();
        }

        return s;
    }

private:
    const GEDT &f;
    const OCTree &tree;

    std::default_random_engine generator;
    std::discrete_distribution<int> distribution;

};

#endif //SYMMETRY_DETECTION_SAMPLER_H
