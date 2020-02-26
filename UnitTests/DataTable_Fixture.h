/* 
 * File:   DataTable_Fixture.h
 * Author: bushoi
 *
 * Created on 24 February 2020, 23:33
 */

#ifndef DATATABLE_FIXTURE_H
#define	DATATABLE_FIXTURE_H

#include <gtest/gtest.h>

#include "DataTable.h"

#include <memory>

class DataTable_Fixture : public ::testing::Test 
{
    public:
        DataTable_Fixture() = default;
        virtual ~DataTable_Fixture() = default;
        
    protected:
        /** 
         * Setup the test.
         */
        void SetUp() override;

        /** 
         * Tear down after the test.
         */
        void TearDown() override;
        
        template< typename It >
        void loadNumbers( It b, It e )
        { while( b != e ) this->iTable->insertNumber( *b++ ); }

        DataTable& dataTable();
        
    private:
        std::shared_ptr<DataTable> iTable;

};

#endif	/* DATATABLE_FIXTURE_H */

