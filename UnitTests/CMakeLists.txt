project(FTR-UnitTests)

include_directories( ~/include ../DataEntry )
link_directories( ~/lib )

add_executable(FTR-UnitTests main.cpp 
	BigNumber_Fixture.cpp BigNumber_Tests.cpp 
	DataTable_Fixture.cpp DataTable_Tests.cpp 
	FibMatch_Fixture.cpp FibMatch_Tests.cpp
	../DataEntry/BigNumber.cpp 
	../DataEntry/CommandReader.cpp 
	../DataEntry/DataEntryEngine.cpp 
	../DataEntry/DataTable.cpp 
	../DataEntry/FibonacciMatcher.cpp)

target_link_libraries(FTR-UnitTests gtest pthread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
