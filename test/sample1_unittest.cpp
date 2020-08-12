#include "gtest/gtest.h"
#include "../src/driver.hh"

namespace
{
    TEST(ADD, Trivial)
    {
        driver drv;

        drv.parse_string ("20+30+15+10\n");
        EXPECT_EQ(drv.result, 75);

        drv.parse_string ("20+30+15+10.0\n");
        EXPECT_EQ(drv.result, 75.0);

        drv.parse_string ("1.5+10.0+10.0\n");
        EXPECT_EQ(drv.result, 21.5);

        drv.parse_string ("1.5 + (-0.5)\n");
        EXPECT_EQ(drv.result, 1.0);

        drv.parse_string ("1 + (-1)\n");
        EXPECT_EQ(drv.result, 0);
    }
    TEST(SUBTRACT, Trivial)
    {
        driver drv;

        drv.parse_string ("20-10\n");
        EXPECT_EQ(drv.result, 10);

        drv.parse_string ("1-0.5\n");
        EXPECT_EQ(drv.result, 0.5);

        drv.parse_string ("21.0-1.0\n");
        EXPECT_EQ(drv.result, 20.0);
    }
}
