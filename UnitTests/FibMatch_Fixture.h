/* 
 * File:   FibMatch_Fixture.h
 * Author: bushoi
 *
 * Created on 24 February 2020, 20:25
 */

#ifndef FIBMATCH_FIXTURE_H
#define	FIBMATCH_FIXTURE_H

#include <gtest/gtest.h>

#include "FibonacciMatcher.h"

class FibMatch_Fixture : public ::testing::Test {
    public:
        FibMatch_Fixture();
        virtual ~FibMatch_Fixture() = default;
        
    protected:
        const FibonacciMatcher& iMatcher;
};

#endif	/* FIBMATCH_FIXTURE_H */

