/* 
 * File:   FibMatch_Tests.cpp
 * Author: bushoi
 * 
 * Created on 24 February 2020, 20:24
 */

#include "FibMatch_Fixture.h"

#include <vector>

namespace UnitTests{
    
    typedef std::vector< BigNumber > tBigNumberList;
    
    TEST_F( FibMatch_Fixture, FibonacciMatcher_NotInSeries )
    {
        tBigNumberList lNotInSeriesList { 
            { "4" },
            { "6" },
            { "07" },
            { "9" },
            { "609" },
            { "611" },
            { "14913169640232740127827512057302148063648650711209401966150219926546779697987984279570098768737999680" },
            { "14913169640232740127827512057302148063648650711209401966150219926546779697987984279570098768737999682" },
            {"43466557686937456435688527675040625802564660517371780402481729089536555417949051890403879840079255169295922593080322634775209689623239873322471161642996440906533187938298969649928516003704476137795166849228875" }
        };
        
        tBigNumberList::const_iterator i, e = lNotInSeriesList.cend();
        
        for ( i = lNotInSeriesList.cbegin(); i != e; ++i )
            ASSERT_FALSE( iMatcher.contains( *i ) ) << *i << " isn't a Fibonacci number! ";
    }
    
    TEST_F( FibMatch_Fixture, FibonacciMatcher_InSeries )
    {
        tBigNumberList lInSeriesList { 
            { "0" },
            { "000" },
            { "1" },
            { "3" },
            { "377" },
            { "514229" },
            { "12776523572924732586037033894655031898659556447352249" },
            { "26863810024485359386146727202142923967616609318986952340123175997617981700247881689338369654483356564191827856161443356312976673642210350324634850410377680367334151172899169723197082763985615764450078474174626" },
            { "243725736716855736962686024334547386493350883030562350014156803065122954698190550443767391293292996385624461466575000597686778187" }
        };
        
        tBigNumberList::const_iterator i, e = lInSeriesList.cend();
        
        for ( i = lInSeriesList.cbegin(); i != e; ++i )
            ASSERT_TRUE( iMatcher.contains( *i ) ) << *i << " IS a Fibonacci number! ";
    }
    
}