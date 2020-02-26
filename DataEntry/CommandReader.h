/* 
 * File:   CommandReader.h
 * Author: bushoi
 *
 * Created on 23 February 2020, 11:02
 */

#ifndef COMMANDREADER_H
#define	COMMANDREADER_H

#include "CommandObserver.h"
#include "FibonacciMatcher.h"

#include <iostream>

/**
 * User I/O component that interacts with the user
 * to receive initialising data, and ongoing commands.
 */
class CommandReader {
public:
    /**
     * Command input mode 
     */
    enum class Mode { 
        /** NULL mode */
        CRM_NULL = 0,
        
        /** Report period input */
        CRM_Period,
        
        /** First number entry */
        CRM_FirstNumber,
        
        /** Waiting for user to enter a command (P, R, N, or Q) */
        CRM_Instruction,
        
        /** Next Number entry */
        CRM_NextNumber
    };
    
    /**
     * Constructor
     * @param aCommandSource    The istream that commands are read from
     * @param aPromptStream     The ostream where the user prompts will be sent.
     * @param aObserver         An object that will receive command notifications.
     */
    CommandReader( std::istream& aCommandSource, std::ostream& aPromptStream, CommandObserver& aObserver );
    
    /**
     * Destructor
     */
    virtual ~CommandReader() = default;
    
    /**
     * Thread entry-point
     */
    void operator()();

protected:
    /**
     * Does the CommandBuffer contain a complete command.
     */
    bool commandComplete() const;
    
    /**
     * Deliver the collected command to the CommandReceiver
     */
    void deliverCommand();
    
    /**
     * Supply User Prompt for the current Input Mode
     * @return  User Prompt
     */
    const std::string& getPrompt() const;
    
private:
    
    /** 
     * The thread entry-point function is to continue running. 
     */
    bool iRunning;

    /**
     * istream from which the commands are read  
     */
    std::istream& iCommandStream;
    
    /**
     * ostream where output is to be sent.
     */
    std::ostream& iPromptStream;
    
    /**
     * Current Command input mode.
     */
    Mode iInputMode;
    
    /**
     * Command BUffer
     */
    std::string iCommandBuffer;
    
    /**
     * The Command Receiver.
     */
    CommandObserver& iCommandReceiver;
    
    /**
     * Fibonacci Matcher
     */
    FibonacciMatcher& iMatcher;
};

#endif	/* COMMANDREADER_H */

