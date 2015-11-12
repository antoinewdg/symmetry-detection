#include "prst/prst.h"

PRST::PRST(const GEDT &f) : f(f), grid(f.getGrid()), sampler(f) {
    vector<Vec> samplesA(sampler.samples(2 * grid.size2)),
            samplesB(sampler.samples(2 * grid.size2));

//    Plane

    for(Vec& x : samplesA){
        for(Vec& y : samplesB){

        }
    }
}