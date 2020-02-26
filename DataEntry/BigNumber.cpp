/* 
 * File:   BigNumber.cpp
 * Author: bushoi
 * 
 * Created on 23 February 2020, 21:16
 */

#include "BigNumber.h"
#include <algorithm>

//
// Implementation for InvalidNumberException
//
InvalidNumberException::InvalidNumberException( const std::string& aBadNumber )
  : iInvalidNumber( aBadNumber )
{    
}

const char*
InvalidNumberException::what()
const noexcept
{
    if ( this->iDescription.empty() )
    {
        this->iDescription = "Invalid value for BigNumber: ";
        this->iDescription.append( this->iInvalidNumber );
    }
    
    return this->iDescription.data();
}

/**
 * Remove any preceding '0' from given string.
 * @param aUntrimmed
 * @return 
 */
std::string trim( const std::string& aUntrimmed )
{
    std::string lReturn;    
    std::string::size_type lFirstNonZero = aUntrimmed.find_first_not_of( "0" );

    if ( lFirstNonZero == std::string::npos ) {
        lReturn = "0";
    } else {
        lReturn = aUntrimmed.substr( lFirstNonZero );
    }
    
    return lReturn;
}

//
// Implementation of BigNumber
//
BigNumber::BigNumber() {
}

BigNumber::BigNumber( const BigNumber& aOther ) 
  : std::string( aOther )
{
}

BigNumber::BigNumber( const std::string& aValueString )
  : std::string( trim( aValueString ) )
{
    if ( this->find_first_not_of( "0123456789" ) != std::string::npos )
        throw InvalidNumberException( aValueString );
}

BigNumber::BigNumber( BigNumber&& aOther )
  : std::string( aOther )
{    
}

BigNumber::BigNumber( std::string&& aValueString )
 : std::string( trim( aValueString ) )
{    
    if ( this->find_first_not_of( "0123456789" ) != std::string::npos )
        throw InvalidNumberException( aValueString );
}

BigNumber&
BigNumber::operator=( const BigNumber& aOther )
{
    this->std::string::operator=( aOther );
    return *this;
}

BigNumber&
BigNumber::operator=( BigNumber&& aOther )
{
    this->std::string::operator=( aOther );
    return *this;
}

bool
BigNumber::operator<( const BigNumber& aOther )
const
{
    std::string::size_type lThisLength = this->length();
    std::string::size_type lOtherLength = aOther.length();
    
    // If 'this' is shorter it's definitely less
    bool lReturn = lThisLength < lOtherLength;
    
    // If the strings are the same length, we'll need to inspect the digits
    if ( lThisLength == lOtherLength ) {
        
        // Find the first digit that varies between the strings
        std::pair< std::string::const_iterator, std::string::const_iterator > lMismatches =
                std::mismatch ( this->cbegin(), this->cend(),
                    aOther.cbegin() );
        
        // If we didn't get to the end of the strings, we have a varying digit.
        // A direct comparison on that character will given the correct response. 
        
        lReturn = lMismatches.first != this->cend() &&
                  lMismatches.second != aOther.cend() &&
                  *lMismatches.first < *lMismatches.second;
    }
    
    return lReturn;
}