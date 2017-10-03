//
// Created by Александр on 29.9.2017
//
#ifdef _GTEST
#include <gtest/gtest.h>

#endif

using namespace std;

int main(int argc, char *argv[])
{
#ifdef _GTEST
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    return 0;
}
