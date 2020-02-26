cmake_minimum_required(VERSION 3.0)

project(FTR-DataEntry)

add_executable(FTR-DataEntry main.cpp BigNumber.cpp CommandReader.cpp DataEntryEngine.cpp DataTable.cpp FibonacciMatcher.cpp)

#
# pthread was required for GNU/Linux's implementation
# of the C++ Threading library. Your toolchain may
# not require this, or may require alternatives.
#
target_link_libraries(FTR-DataEntry pthread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
