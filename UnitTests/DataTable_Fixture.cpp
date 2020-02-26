/* 
 * File:   DataTable_Fixture.cpp
 * Author: bushoi
 * 
 * Created on 24 February 2020, 23:33
 */

#include "DataTable_Fixture.h"

void
DataTable_Fixture::SetUp() {
    this->iTable.reset(new DataTable);
}

void
DataTable_Fixture::TearDown() {
    this->iTable.reset();
}

DataTable&
DataTable_Fixture::dataTable()
{
    return *this->iTable;
}
