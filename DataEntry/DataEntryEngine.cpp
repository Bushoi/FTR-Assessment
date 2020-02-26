/* 
 * File:   DataEntryEngine.cpp
 * Author: bushoi
 * 
 * Created on 23 February 2020, 16:40
 */

#include "DataEntryEngine.h"

#include <iostream>

//
// Some inserters to aid debugging 
//
template< class Rep2, class Period2 >
std::ostream& operator<<( std::ostream& aOS, const std::chrono::duration<Rep2,Period2>& aDuration )
{ 
    aOS << std::chrono::duration_cast< std::chrono::duration< double, std::milli > >( aDuration ).count();
    return aOS;
}

//
// DataEntryEngine implementation.
//

DataEntryEngine::DataEntryEngine( std::ostream& aOS )
  : iOutStream( aOS ),
    iRunning( true ),
    iTimerEnabled( false ),
    iTimerStateChange( false ),
    iPeriodAccrued( 0 )
{ }

void
DataEntryEngine::reportPeriod( uint64_t aPeriodSecs )
{
    // Record the report timer period
    this->iPeriod_ms = std::chrono::seconds( aPeriodSecs );
}

bool DataEntryEngine::enginePause() 
{
    std::unique_lock<std::mutex> lPauseLock( this->iDeliverMutex );

    // Reset and signal change
    if ( this->iTimerEnabled ) {
        this->iTimerEnabled = false;
        this->iTimerStateChange = true;
    }

    // Notify
    this->iDeliverCV.notify_one();
    return !this->iTimerEnabled;
}

bool DataEntryEngine::engineRun() 
{
    std::unique_lock<std::mutex> lRunLock( this->iDeliverMutex );
    
    // Set and signal change
    if ( ! this->iTimerEnabled ) {
        this->iTimerEnabled = true;
        this->iTimerStateChange = true;
    }
    
    // Adjust StartMark so that it includes time that passed 
    // before the pause
    this->iStartMark = tClock::now() - this->iPeriodAccrued;
    this->iPeriodAccrued = tClock::duration( 0 );
    
    // Notify
    this->iDeliverCV.notify_one();
    return this->iTimerEnabled;
}

void DataEntryEngine::engineQuit() 
{
    // Signal end of processing and notify
    std::unique_lock<std::mutex> lQuitLock( this->iDeliverMutex );
    this->iRunning = false;
    this->iDeliverCV.notify_one();
}

void DataEntryEngine::numberEntry() 
{ }

void DataEntryEngine::numberComplete( const BigNumber& aNewNumber ) 
{
    // Record the number in the DataTable.
    this->iTable.insertNumber( aNewNumber );
}

void DataEntryEngine::operator()()
{
    std::unique_lock<std::mutex> lCommandLock( this->iDeliverMutex );
        
    while( this->iRunning ) {
        
        // Reset Timer change notification flag
        this->iTimerStateChange = false;
        
        // If automatic reporting is enabled
        if ( this->iTimerEnabled ) {
            
            // Determine the EndMark of the period
            tClock::time_point lEndMark( this->iStartMark + this->iPeriod_ms );
                        
            // Wait for command or end of timer
            if ( ! this->iDeliverCV.wait_until( lCommandLock, lEndMark, [this]{ return !iRunning || iTimerStateChange; } ) ) {
                
                // timeout, report and start another period
                this->printFrequencies();               
                this->iStartMark = lEndMark;
                
            } else if ( this->iTimerStateChange && ! this->iTimerEnabled ) {
                
                // Pause has been signalled, take not of the time that has passed 
                // for the current period, the remainder will be used
                // when we resume reporting
                this->iPeriodAccrued = tClock::now() - this->iStartMark;
            
            }
        } else {
            
            // Just wait for a command...
            this->iDeliverCV.wait( lCommandLock, [this]{ return !iRunning || iTimerStateChange; } );

        }
    }
    
    // Final print of the report
    this->printFrequencies();
}

void
DataEntryEngine::printFrequencies() 
const
{
    this->iOutStream << this->iTable.getFrequencies() << std::endl << std::flush;   
}