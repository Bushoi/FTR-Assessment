/* 
 * File:   FibonacciMatcher.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 23:04
 */

#ifndef FIBONACCIMATCHER_H
#define	FIBONACCIMATCHER_H

#include "BigNumber.h"

#include <set>

/**
 * Matches numbers against the first 1000 numbers in the Fibonacci
 * sequence
 */
class FibonacciMatcher {
    public:
        /**
         * Singleton getter.
         * @return A FibonacciMatcher (singleton) 
         */
        static FibonacciMatcher& get();
        
        /**
         * Matches the given number with any in the sequence.
         * @param aFind  Number being matched.
         * @return Boolean indicating if the given number was found.
         */
        bool contains( const BigNumber& aFind ) const;
        
    private:
        /**
         * Default constructor.
         */
        FibonacciMatcher();
        
        /** 
         * Destructor.
         */
        virtual ~FibonacciMatcher();
        
        /**
         * The single instance of FibonacciMatcher.
         */
        static FibonacciMatcher cSingleton;

        /**
         * The set of BigNumbers that contains the full sequence.
         * All 1000 of the first Fibonacci numbers are loaded into this set.
         */
        std::set<BigNumber> iNumberSet;
};

#endif	/* FIBONACCIMATCHER_H */

