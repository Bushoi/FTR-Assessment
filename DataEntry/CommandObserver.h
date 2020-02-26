/* 
 * File:   CommandObserver.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 13:10
 */

#ifndef COMMANDOBSERVER_H
#define	COMMANDOBSERVER_H

#include "BigNumber.h"

#include <cstdlib>

/**
 * The CommandObserver interface.
 * 
 * A pure-virtual class to be implemented by any class
 * that wants to subscribe to events from the CommandReader.
 * 
 */
class CommandObserver {
public:
    /**
     * Set the duration between the timer controlled reports.
     * @param aPeriodSecs   Number of seconds between each report.
     */
    virtual void reportPeriod( uint64_t aPeriodSecs ) = 0;
    
    /**
     * Pause the timer generated reports.
     * No more reports will be automatically generated. The time
     * that has passed since the last report will be recorded, and 
     * when reporting is re-enabled the remaining time of the period
     * will be timed before the next report. After that the reporting 
     * period will return to the original value.
     * @return Boolean indicating that the command was processed.
     */
    virtual bool enginePause() = 0;
    
    /**
     * Re-enable the timer generated reports. The time remaining from the 
     * previous period before it was suspended will be allowed to pass
     * before the next report if generated. After that the reporting 
     * period will return to the original value.
     * @return Boolean indicating that the command was processed.
     */
    virtual bool engineRun() = 0;
    
    /**
     * Shutdown.
     * Halt processing, release resources, and produce final report.
     */
    virtual void engineQuit() = 0;
    
    /**
     * New number command.
     * The next number is being entered, and will be supplied shortly.
     * numberComplete() will be called with the entered number.
     */
    virtual void numberEntry() = 0;
    
    /**
     * A new number has been entered.
     * @param aNewNumber  The new number.
     */
    virtual void numberComplete( const BigNumber& aNewNumber ) = 0;    
};

#endif	/* COMMANDOBSERVER_H */

