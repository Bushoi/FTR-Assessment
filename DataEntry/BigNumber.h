/* 
 * File:   BigNumber.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 21:16
 */

#ifndef BiGNUMBER_H
#define	BiGNUMBER_H

#include <string>

/**
 * InvalidNumberNumber.
 * Thrown when the entered string does not contain a valid
 * number. 
 */
class InvalidNumberException : public std::exception
{
    public:
        /**
         * Constructor.
         * @param aBadNumber  The string that doesn't contain a valid number.
         */
        InvalidNumberException( const std::string& aBadNumber );
    
        /**
         * Get a textual description of the exception.
         * The returned string is not initialised until
         * the first call.
         * @return Description of exception
         */
        const char* what() const noexcept override;
        
    private:
        /** The invalid number string*/
        std::string iInvalidNumber;
        
        /** The description of the exception */
        std::string mutable iDescription;
};

/**
 * A big number represented as a string of numeric digits.
 */
class BigNumber : public std::string
{
    public:
        /** 
         * Default constructor. 
         */
        BigNumber();

        /** 
         * Copy constructor.
         * @param aOther  BigNumber being copied
         */
        BigNumber( const BigNumber& aOther );
        
        /**
         * Copy construct from string.
         * The contents of the string will be checked 
         * to make sure it only contains digits.
         * @param aValueString
         */
        BigNumber( const std::string& aValueString );

        /**
         * Move constructor.
         * @param aOther  BigNumber being moved
         */
        BigNumber( BigNumber&& aOther );
        
        /**
         * Move construct from string. 
         * The contents of the string will be checked 
         * to make sure it only contains digits.
         * @param aValueString
         */
        BigNumber( std::string&& aValueString );

        /**
         * Copy assignment.
         * @param aOther BigNumber whose value will be copied.
         * @return 
         */
        BigNumber& operator=( const BigNumber& aOther );
        
        /**
         * Move assignment.         
         * @param aOther  BigNumber whose value will be moved.
         * @return 
         */
        BigNumber& operator=( BigNumber&& aOther );

        /**
         * Destructor.
         */
        virtual ~BigNumber() = default;

        /**
         * Less than comparator.
         * 
         * The comparison is made on the numeric values of
         * the given BigNumbers.
         * 
         * @param aOther  BigNumber being compared against.
         * @return Boolean indicating if this BigNumner is less-than aOther
         */
        bool operator<( const BigNumber& aOther ) const;
};

#endif	/* BIGNUMBER_H */

