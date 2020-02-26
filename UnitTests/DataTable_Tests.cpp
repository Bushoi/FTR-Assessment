/* 
 * File:   DataTable_Tests.cpp
 * Author: bushoi
 * 
 * Created on 24 February 2020, 22:15
 */

#include "DataTable_Fixture.h"

namespace UnitTests {
    
    TEST_F( DataTable_Fixture, DataTable_Test1 ) 
    {
        std::vector< BigNumber > lInputNumbers {
            {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"4"}, {"3"}, {"2"}, 
            {"1"}, {"3"}, {"5"}, {"3"}, {"1"}, {"5"}, {"5"}, {"5"}            
        };
        
        this->DataTable_Fixture::loadNumbers( lInputNumbers.cbegin(), lInputNumbers.cend() );
        
        tValueFreqList lOutput( this->DataTable_Fixture::dataTable().getFrequencies() );
        
        ASSERT_EQ( lOutput.size(), 5U ) << "Didn't record all of the numbers";
        
        ASSERT_EQ( lOutput[0], tValueFrequencyPair( "5", 5 ) );
        ASSERT_EQ( lOutput[1], tValueFrequencyPair( "3", 4 ) );
        ASSERT_EQ( lOutput[2], tValueFrequencyPair( "1", 3 ) );
        ASSERT_EQ( lOutput[3], tValueFrequencyPair( "2", 2 ) );
        ASSERT_EQ( lOutput[4], tValueFrequencyPair( "4", 2 ) );
    }

    TEST_F( DataTable_Fixture, DataTable_Test2 ) 
    {
        std::vector< BigNumber > lInputNumbers {
            {"0"},
            {"70492524767089125814114"}, 
            {"11111460156937785151929026842503960837766832936"}, 
            {"1751455877444438095408940282208383549115781784912085789506677971125378"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"43516638122555047989641805373140394725407202037260729735885664398655775748034950972577909265605502785297675867877570"}, 
            {"6859356963880484413875401302176431788073214234535725264860437720157972142108894511264898366145528622543082646626140527097739556699078708088"}, 
            {"26863810024485359386146727202142923967616609318986952340123175997617981700247881689338369654483356564191827856161443356312976673642210350324634850410377680367334151172899169723197082763985615764450078474174626"}, 
            {"11111460156937785151929026842503960837766832936"}, 
            {"1751455877444438095408940282208383549115781784912085789506677971125378"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"43516638122555047989641805373140394725407202037260729735885664398655775748034950972577909265605502785297675867877570"}, 
            {"6859356963880484413875401302176431788073214234535725264860437720157972142108894511264898366145528622543082646626140527097739556699078708088"}, 
            {"26863810024485359386146727202142923967616609318986952340123175997617981700247881689338369654483356564191827856161443356312976673642210350324634850410377680367334151172899169723197082763985615764450078474174626"}, 
            {"11111460156937785151929026842503960837766832936"}, 
            {"1751455877444438095408940282208383549115781784912085789506677971125378"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"43516638122555047989641805373140394725407202037260729735885664398655775748034950972577909265605502785297675867877570"}, 
            {"6859356963880484413875401302176431788073214234535725264860437720157972142108894511264898366145528622543082646626140527097739556699078708088"}, 
            {"1751455877444438095408940282208383549115781784912085789506677971125378"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"43516638122555047989641805373140394725407202037260729735885664398655775748034950972577909265605502785297675867877570"}, 
            {"6859356963880484413875401302176431788073214234535725264860437720157972142108894511264898366145528622543082646626140527097739556699078708088"}, 
            {"1751455877444438095408940282208383549115781784912085789506677971125378"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408"}, 
            {"0"}            
        };
        
        this->DataTable_Fixture::loadNumbers( lInputNumbers.cbegin(), lInputNumbers.cend() );
        
        tValueFreqList lOutput( this->DataTable_Fixture::dataTable().getFrequencies() );
        
        ASSERT_EQ( lOutput.size(), 8U ) << "Didn't record all of the numbers";
        
        ASSERT_EQ( lOutput[0], tValueFrequencyPair( "276075119498972121378113841488282573748675897900397028699360341995399351640458606953841075408", 6 ) );
        ASSERT_EQ( lOutput[1], tValueFrequencyPair( "1751455877444438095408940282208383549115781784912085789506677971125378", 5 ) );
        ASSERT_EQ( lOutput[2], tValueFrequencyPair( "43516638122555047989641805373140394725407202037260729735885664398655775748034950972577909265605502785297675867877570", 4 ) );
        ASSERT_EQ( lOutput[3], tValueFrequencyPair( "6859356963880484413875401302176431788073214234535725264860437720157972142108894511264898366145528622543082646626140527097739556699078708088", 4 ) );
        ASSERT_EQ( lOutput[4], tValueFrequencyPair( "11111460156937785151929026842503960837766832936", 3 ) );
        ASSERT_EQ( lOutput[5], tValueFrequencyPair( "0", 2 ) );
        ASSERT_EQ( lOutput[6], tValueFrequencyPair( "26863810024485359386146727202142923967616609318986952340123175997617981700247881689338369654483356564191827856161443356312976673642210350324634850410377680367334151172899169723197082763985615764450078474174626", 2 ) );
        ASSERT_EQ( lOutput[7], tValueFrequencyPair( "70492524767089125814114", 1 ) );
    }

    TEST_F( DataTable_Fixture, DataTable_Test3 ) 
    {
        BigNumber lBN1( "1" ), lBN2( "2" ), lBN3( "3" ), lBN4( "4" );
        
        for ( int i = 0; i < 10000; ++i ) this->dataTable().insertNumber( lBN1 );
        for ( int i = 0; i < 1000; ++i ) this->dataTable().insertNumber( lBN2 );
        for ( int i = 0; i < 100000; ++i ) this->dataTable().insertNumber( lBN3 );
        for ( int i = 0; i < 100001; ++i ) this->dataTable().insertNumber( lBN4 );              
                
        tValueFreqList lOutput( this->DataTable_Fixture::dataTable().getFrequencies() );
        
        ASSERT_EQ( lOutput.size(), 4U ) << "Didn't record all of the numbers";
        
        ASSERT_EQ( lOutput[0], tValueFrequencyPair( "4", 100001 ) );
        ASSERT_EQ( lOutput[1], tValueFrequencyPair( "3", 100000 ) );
        ASSERT_EQ( lOutput[2], tValueFrequencyPair( "1", 10000 ) );
        ASSERT_EQ( lOutput[3], tValueFrequencyPair( "2", 1000 ) );
    }

}