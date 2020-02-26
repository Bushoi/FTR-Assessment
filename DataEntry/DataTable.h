/* 
 * File:   DataTable.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 19:57
 */

#ifndef DATATABLE_H
#define	DATATABLE_H

#include "BigNumber.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <set>
#include <map>

#include <mutex>

#include <ostream>

/**
 * Value-Frequency pair.
 * Used to store statistical data about the number being
 * stored in the DataTable.
 */
typedef std::pair<BigNumber, uint64_t> tValueFrequencyPair;

/**
 * Shared-pointer to the Value-Frequency pair.
 */
typedef std::shared_ptr< tValueFrequencyPair > spValueFreqPair;

/**
 * Function class that compares the Values between two Value-Frequency pairs.
 * Designed to be used on spValueFreqPair, hence the dereferencing.
 */
struct spValueFreqCompare {
    bool operator()( const spValueFreqPair& lhs, const spValueFreqPair& rhs ) const
    { return lhs && rhs && lhs->first < rhs->first; }
};

/**
 * A list of Value-Frequency pairs.
 */
typedef std::vector<tValueFrequencyPair> tValueFreqList;

/**
 * A set of spValueFreqPairm sequenced by their Value.
 */
typedef std::set< spValueFreqPair, spValueFreqCompare > tValueFreqSet;

/**
 * A map of tValueFreqSet sequenced by their frequency.
 */
typedef std::map< uint64_t, tValueFreqSet > tValueFreqByFrequency;

/** 
 * An ostream inserter for tValueFreqList.
 * The value Frequency pairs will be printed in the order they appear in the 
 * vector.
 */
std::ostream& operator<<( std::ostream& aOS, const tValueFreqList& aList );

/**
 * Statistics processing for the DataEntryEngine.
 * Numbers are added to the table where their frequency is monitored
 * and reports are generated.
 */
class DataTable {
    public:
        
        /**
         * Default constructor.
         */
        DataTable() = default;

        /**
         * Destructor.
         */
        virtual ~DataTable() = default;

        /**
         * Insert a number into the DataTable.
         * @param aNewNumber
         */
        void insertNumber( const BigNumber& aNewNumber );
        
        /**
         * Get the frequency report.
         * @return  A list of Value Frequency pairs in the required order.
         */
        tValueFreqList getFrequencies() const;

    private:     
        
        /** 
         * A full list of all the numbers entered into the table
         * and their frequency. 
         */
        tValueFreqSet iFullList;
        
        /**
         * Value Frequency pairs organised by their frequency count.
         */
        tValueFreqByFrequency iByFreqList;
        
        /**
         * Mutex used to maintain coherency in the internal data-structures.
         */
        mutable std::mutex iListLock;
};

#endif	/* DATATABLE_H */

