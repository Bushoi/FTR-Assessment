/* 
 * File:   DataEntryEngine.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 16:40
 */

#ifndef DATAENTRYENGINE_H
#define	DATAENTRYENGINE_H

#include "CommandObserver.h"
#include "DataTable.h"

#include <set>
#include <ostream>

#include <mutex>
#include <condition_variable>
#include <chrono>

/** Use the high-precision clock. */
typedef std::chrono::high_resolution_clock tClock;

/**
 * The data processing and reporting component.
 * Receives a series of numbers, counts their frequency, and
 * provides reports on occurrence and frequency of the numbers 
 * being supplied to the DataEntryEngine.
 * 
 * The reports are automatically generated at regular periods, and
 * when the engine is shutdown.
 */
class DataEntryEngine : public CommandObserver 
{
public:
    
    /**
     * Constructor.
     * @param aOS  std::ostream where reports will be written
     */
    DataEntryEngine( std::ostream& aOS );
    
    /**
     * Destructor.
     */
    virtual ~DataEntryEngine() = default;
    
    /**
     * Implementation of CommandObserver::reportPeriod()
     * @param aPeriodSecs
     */
    void reportPeriod( uint64_t aPeriodSecs );
    
    /**
     * Implementation of CommandObserver::enginePause()
     */
    bool enginePause() override;
    
    /**
     * Implementation of CommandObserver::engineRun()
     */
    bool engineRun() override;
    
    /**
     * Implementation of CommandObserver::engineQuit()
     */
    void engineQuit() override;
    
    /**
     * Implementation of CommandObserver::numberEntry()
     */
    void numberEntry() override;

    /**
     * Implementation of CommandObserver::numberComplete()
     * @param aNewNumber
     */
    void numberComplete( const BigNumber& aNewNumber ) override;
    
    /**
     * Thread entry-point
     */
    void operator()();
    
protected:
    /**
     * Print the frequencies report.
     */
    void printFrequencies() const;
    
private:
    /**
     * DataTable where numbers delivered through numberComplete() are 
     * recorded, and the reports are generated.
     */
    DataTable iTable;
    
    /**
     * std::ostream where reports are written to.
     */
    std::ostream& iOutStream;
    
    /**
     * Keep the engine (thread) running
     */
    bool iRunning;
    
    /**
     * Report timer is currently enabled.
     */
    bool iTimerEnabled;
    
    /**
     * Inter-thread notification that iTimerEnabled has changed state.
     */
    bool iTimerStateChange;
    
    /**
     * The period between automatic reports. 
     */
    std::chrono::milliseconds iPeriod_ms;
    
    /**
     * How much time had passed in the previous reporting period 
     * before the engine was paused.
     */
    tClock::duration iPeriodAccrued;
    
    /**
     * Start of the current reporting timer period.
     */
    tClock::time_point iStartMark;
    
    /**
     * Mutex that provides mutual  exclusion for thread interactions.
     */
    std::mutex iDeliverMutex;
    
    /**
     * Condition Variable that manages thread interactions.
     */
    std::condition_variable iDeliverCV;
};

#endif	/* DATAENTRYENGINE_H */

