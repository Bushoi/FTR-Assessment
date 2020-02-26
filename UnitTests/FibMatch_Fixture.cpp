/* 
 * File:   FibMatch_Fixture.cpp
 * Author: bushoi
 * 
 * Created on 24 February 2020, 20:25
 */

#include "FibMatch_Fixture.h"

FibMatch_Fixture::FibMatch_Fixture() 
  : iMatcher( FibonacciMatcher::get() )
{
}
