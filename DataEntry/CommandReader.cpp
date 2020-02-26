/* 
 * File:   CommandReader.cpp
 * Author: bushoi
 * 
 * Created on 23 February 2020, 11:02
 */

#include "CommandReader.h"
#include "CommandObserver.h"

#include <cstdio>
#include <map>

/**
 * Unrecognised Command exception
 */
class UnrecognisedCommandException : public std::exception
{
    public:
        /** 
         * Copy-Constructor.
         * @param aInvalidCommand  The invalid command
         */
        UnrecognisedCommandException( const std::string& aInvalidCommand )
          : iInvalidCommand( aInvalidCommand )
        {}
          
          /**
           * Move-Constructor
           * @param aInvalidCommand The invalid command
           */
        UnrecognisedCommandException( std::string&& aInvalidCommand )
          : iInvalidCommand( aInvalidCommand )
        {}
        
        /**
         * Describe the exception
         * @return Description
         */
        const char* what() const noexcept override
        {            
            if ( this->iDescription.empty() ) {
                this->iDescription = "Unrecognised command: ";
                this->iDescription.append( this->iInvalidCommand );
            }
            
            return this->iDescription.data();
        }
        
    private:
        /** The Invalid Command itself */
        std::string iInvalidCommand;
        std::string mutable iDescription;
            
};

/**
 * Bad Number Exception
 */
class InvalidPeriodException : public std::exception
{
    public:
        /** 
         * Copy-Constructor
         * @param aBadNumber  The string that doesn't contain a valid number
         */
        InvalidPeriodException( const std::string& aBadNumber )
          : iBadNumber( aBadNumber )
        {}
          
        /** 
         * Move-Constructor
         * @param aBadNumber  The string that doesn't contain a valid number
         */
        InvalidPeriodException( std::string&& aBadNumber )
          : iBadNumber( aBadNumber )
        {}
          
        /**
         * Describe the exception
         * @return Description
         */
        const char* what() const noexcept override
        {
            if ( this->iDescription.empty() ) {
                this->iDescription = "Invalid period: ";
                this->iDescription.append( this->iBadNumber );
            }
            
            return this->iDescription.data();
        }
        
    private:
        /** The string that couldn't be converted to a number */
        std::string iBadNumber;
        std::string mutable iDescription;
};

//
// Implementation of CommandReader
//

CommandReader::CommandReader( std::istream& aCommandSource, std::ostream& aPromptStream, CommandObserver& aObserver )
  : iCommandStream( aCommandSource ),
    iPromptStream( aPromptStream ),
    iInputMode( Mode::CRM_Period ),
    iCommandReceiver( aObserver ),
    iMatcher( FibonacciMatcher::get() )
{
}

//
// The thread entry-point
// This method will return when processing is complete.
// Signalled either by the user entering the quit command
// or by EOF being received on the input stream where commands
// are being received.
//
void CommandReader::operator ()()
{
    char lCharRead;
    
    this->iRunning = true;
    
    // Read characters until stdin is closed
    while( ! this->iCommandStream.eof() && iRunning )
    {
        try {
            this->iPromptStream << this->getPrompt() << std::flush;
            
            while ( ! this->commandComplete() && ! this->iCommandStream.eof() ) {
                lCharRead = this->iCommandStream.get();
                this->iCommandBuffer.append( 1, lCharRead );
            }
            
            if ( lCharRead != std::istream::traits_type::eof() )
            {
                if ( this->commandComplete() )
                {
                    this->deliverCommand();
                }
            } else {
                // EOF, shutdown
                this->iCommandReceiver.engineQuit();
            }
            
        } catch ( const std::exception& eE ) {
            std::cerr << "EXCEPTION: " << eE.what() << std::endl;
        }
        
        this->iCommandBuffer.clear();
    }
}

bool CommandReader::commandComplete()
const
{
    return this->iCommandBuffer.back() == '\n';
}

void CommandReader::deliverCommand()
{
    if ( this->iInputMode == Mode::CRM_Period ) {
        //
        // Report period entry
        //
        try {
            uint64_t lPeriod = std::stoull( this->iCommandBuffer );

            if ( lPeriod > 0 ) {
                this->iCommandReceiver.reportPeriod( lPeriod );
                this->iInputMode = Mode::CRM_FirstNumber;
            }
        } catch ( std::exception& eE ) {
            throw InvalidPeriodException( this->iCommandBuffer );
        }
        
    } else if ( this->iInputMode == Mode::CRM_Instruction ) {
        //
        // Command Entry: Pause, Resume, or Quit
        //
        std::string::size_type lTerm = this->iCommandBuffer.find_first_of( "\r\n" );
        if( lTerm != std::string::npos) {
            this->iCommandBuffer.erase( lTerm );
        }
        
        if ( this->iCommandBuffer.length() == 1 ) {
            
            switch ( this->iCommandBuffer.front() ) {
                case 'N':
                    this->iCommandReceiver.numberEntry();
                    this->iInputMode = Mode::CRM_NextNumber;
                    break;

                case 'P':
                    if ( this->iCommandReceiver.enginePause() )
                        this->iPromptStream << "Timer is paused." << std::endl << std::flush;
                    break;

                case 'R':
                    if ( this->iCommandReceiver.engineRun() ) 
                        this->iPromptStream << "Timer is running." << std::endl << std::flush;
                    break;

                case 'Q':
                    this->iCommandReceiver.engineQuit();
                    this->iRunning = false;
                    break;

                default:
                    throw UnrecognisedCommandException( this->iCommandBuffer );
            };
            
        } else if ( ! this->iCommandBuffer.empty() ) {
            throw UnrecognisedCommandException( this->iCommandBuffer );
        }
        
    } else {
        //
        // Number Entry, either first or next
        //
        std::string::size_type e = this->iCommandBuffer.find_last_not_of( "\r\n" );
        this->iCommandBuffer.erase( e + 1 );

        BigNumber lNewNumber( this->iCommandBuffer );

        this->iCommandReceiver.numberComplete( lNewNumber );        

        if ( this->iInputMode == Mode::CRM_FirstNumber ) {
            
            this->iCommandReceiver.engineRun();
            
        } else {
            // Report if it's one of the first 1000 Fibonacci numbers
            if ( this->iMatcher.contains( lNewNumber ) )
                this->iPromptStream << "FIB!" << std::endl;
        }

        this->iInputMode = Mode::CRM_Instruction;
        
    }
}

const std::string& 
CommandReader::getPrompt() 
const 
{
    static std::map< Mode, std::string > fPrompts {
        { Mode::CRM_NULL, std::string() },
        { Mode::CRM_Period,      "Please enter the output period: " },
        { Mode::CRM_FirstNumber, "Please enter the first number: " },
        { Mode::CRM_NextNumber,  "Please enter the new number: " }
    };
    
    std::map< Mode, std::string >::const_iterator
        f = fPrompts.find( this->iInputMode );
    
    if ( f == fPrompts.cend() )
        f = fPrompts.cbegin();
    
    return f->second;
}
