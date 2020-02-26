/* 
 * File:   BigNumber_Fixture.h
 * Author: bushoi
 *
 * Created on 24 February 2020, 19:24
 */

#ifndef BIGNUMBER_FIXTURE_H
#define	BIGNUMBER_FIXTURE_H

#include <gtest/gtest.h>

#include "BigNumber.h"

namespace UnitTests {
    
    class BigNumber_Fixture : public ::testing::Test
    {
        public:
            BigNumber_Fixture();

            virtual ~BigNumber_Fixture() = default;

        protected:            
            const ::BigNumber iBN_0;
            const ::BigNumber iBN_000;
            const ::BigNumber iBN_1;
            const ::BigNumber iBN_001;
            const ::BigNumber iBN_F10;
            const ::BigNumber iBN_F100;
            const ::BigNumber iBN_F101;
            const ::BigNumber iBN_F999;

        private:

    };
    
}

#endif	/* BIGNUMBER_FIXTURE_H */

