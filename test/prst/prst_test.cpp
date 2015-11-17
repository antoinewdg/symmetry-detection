#include <gtest/gtest.h>
#include <array>
#include "prst/prst.h"
#include "common/common.h"
#include "factory/gedt_factory.h"

TEST(PRST, ConstructsWithoutError) {
    PRST prst(GEDTFactory::basicCube(0, 0, 0, 1, 1, 1));
}