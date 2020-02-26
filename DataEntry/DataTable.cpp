/* 
 * File:   DataTable.cpp
 * Author: bushoi
 * 
 * Created on 23 February 2020, 19:57
 */

#include <set>

#include "DataTable.h"

void 
DataTable::insertNumber( const BigNumber& aNewNumber )
{
    // Mutual exclusion to maintain consistency in the containers/
    std::unique_lock<std::mutex> lAutoLock( this->iListLock );

    // Create a new ValueFrequency pair, and locate it in the FullList
    spValueFreqPair lNewPair( new tValueFrequencyPair( std::make_pair( aNewNumber, 0 ) ) );
    tValueFreqSet::iterator f = this->iFullList.find( lNewPair );
    
    if ( f == this->iFullList.end() ) {
        
        // Not found, need to introduce it.
        lNewPair->second = 1;
        this->iFullList.insert( lNewPair );
        this->iByFreqList[ lNewPair->second ].insert( lNewPair );
        
    } else {
        
        // Already added, locate the per Frequency list using the current count
        tValueFreqByFrequency::iterator f2 = this->iByFreqList.find( (*f)->second );
        
        // If the per Freq list was found
        if ( f2 != this->iByFreqList.end() ) {
            // Remove this ValueFrequency pair from it
            f2->second.erase( *f );
            // And if the per Frequency list is empty, remove that too
            if ( f2->second.empty() ) this->iByFreqList.erase( f2 );
        }
        
        // Increase the frequency counter
        ++(*f)->second;
        
        // Insert the ValueFrequency pair into the per Frequency list
        // for the new frequency
        this->iByFreqList[ (*f)->second ].insert( *f );
    }
}

tValueFreqList 
DataTable::getFrequencies() 
const
{
    tValueFreqList lReturn;
    
    // Mutual exclusion to maintain consistency in the containers/std::unique_lock<std::mutex> lAutoLock( this->iListLock );
    
    // Reverse iterate over the per Frequency List, most frequent are reported first
    tValueFreqByFrequency::const_reverse_iterator i, e = this->iByFreqList.crend();
    for ( i = this->iByFreqList.crbegin(); i != e; ++i )
    {
        // Iterate over the Value Frequency pairs, increasing Value 
        tValueFreqSet::const_iterator i2, e2 = i->second.cend();
        for( i2 = i->second.cbegin(); i2 != e2; ++i2 )
        {
            lReturn.push_back( **i2 );
        }
    }
    
    return lReturn;
}

std::ostream& operator<<( std::ostream& aOS, const tValueFreqList& aList )
{
    tValueFreqList::const_iterator i, 
        b = aList.cbegin(), 
        e = aList.cend();
    
    for ( i = b; i != e; ++i ) {
        if ( i != b ) aOS << ", ";
        aOS << i->first << ":" << i->second;
    }
        
    return aOS;
}