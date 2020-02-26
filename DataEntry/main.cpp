/* 
 * File:   main.cpp
 * Author: bushoi
 *
 * Created on 23 February 2020, 10:59
 */

#include "CommandReader.h"
#include "DataEntryEngine.h"

#include <thread>
#include <iostream>
#include <cstdio>

/*
 * 
 */
int main(int argc, char** argv) 
{
    DataEntryEngine lDEE( std::cout );
    std::thread lEngineThread( &DataEntryEngine::operator(), &lDEE );
    
    // Create and release the CommandReader
    CommandReader lCR( std::cin, std::cout, lDEE );    
    std::thread lReaderThread( &CommandReader::operator(), &lCR );
        
    lReaderThread.join();
    lEngineThread.join();
    
    std::cout << "See you next time!" << std::endl;

    return 0;
}

