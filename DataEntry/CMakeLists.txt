cmake_minimum_required(VERSION 2.8)

project(FTR-DataEntry)

add_executable(FTR-DataEntry main.cpp BigNumber.cpp CommandReader.cpp DataEntryEngine.cpp DataTable.cpp FibonacciMatcher.cpp)
target_compile_options(FTR-DataEntry PUBLIC -std=c++11 )

#
# pthread was required for GNU/Linux's implementation
# of the C++ Threading library. Your toolchain may
# not require this, or may require alternatives.
#
target_link_libraries(FTR-DataEntry pthread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
