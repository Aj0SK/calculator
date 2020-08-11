#include "gtest/gtest.h"
#include "../src/driver.hh"

namespace {

TEST(ADD, Trivial) 
{
    driver drv;
    drv.parse ("aa=5\n5+aa");
    EXPECT_EQ(drv.result, 5);
}

}
