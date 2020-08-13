#include "gtest/gtest.h"
#include "../src/driver.hh"

void test_inputs(const std::vector<std::pair<std::string, double> >& tests)
{
    driver drv;
    for(const auto& test : tests)
    {
        drv.parse_string (test.first);
        EXPECT_EQ(drv.result, test.second);
    }
}

namespace
{
    TEST(ADD, Trivial)
    {
        std::vector<std::pair<std::string, double> > tests = {
            {"20+30+15+10\n", 75},
            {"20+30+15+10.0\n", 75.0},
            {"1.5+10.0+10.0\n", 21.5},
            {"1.5 + (-0.5)\n", 1.0},
            {"1 + (-1)\n", 0}
        };
        test_inputs(tests);
    }
    TEST(SUBTRACT, Trivial)
    {
        std::vector<std::pair<std::string, double> > tests = {
            {"20-10\n", 10},
            {"1-0.5\n", 0.5},
            {"21.0-1.0\n", 20.0},
            {"21.0-(-1.0)\n", 22.0},
        };
        test_inputs(tests);
    }
}
