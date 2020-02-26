/* 
 * File:   BigNumber_Tests.cpp
 * Author: bushoi
 * 
 * Created on 24 February 2020, 19:40
 */

#include "BigNumber_Fixture.h"

namespace UnitTests{
    
    TEST_F( BigNumber_Fixture, BigNumber_Comparisons) {
        ASSERT_TRUE( iBN_0 == iBN_000 ) << "Prefixed zeros aren't being ignored (0 != 000)";
        ASSERT_TRUE( iBN_1 == iBN_001 ) << "Prefixed zeros aren't being ignored (1 != 001)";
        ASSERT_TRUE( iBN_000 < iBN_1 )  << "000 < 1 isn't true!";
        ASSERT_TRUE( iBN_F100 < iBN_F101 ) << "F(100) < F(101) isn't true!";
    }   

}
