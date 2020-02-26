/* 
 * File:   main.cpp
 * Author: bushoi
 *
 * Created on 24 February 2020, 00:11
 */

#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

#include "BigNumber.h"
#include "FibonacciMatcher.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    ::testing::InitGoogleTest(&argc, argv);
    
    int lReturn = RUN_ALL_TESTS();
    
    return 0;
}

