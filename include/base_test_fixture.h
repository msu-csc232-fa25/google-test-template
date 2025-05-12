/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file      base_test_fixture.h
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#ifndef CSC232_BASE_TEST_FIXTURE_H
#define CSC232_BASE_TEST_FIXTURE_H

#include "csc232.h"
#include "gtest/gtest.h"

namespace csc232
{
    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test
    {
    public:
        CSC232BaseTestFixture( ) = default;
        virtual ~CSC232BaseTestFixture( ) override = default;

        CSC232BaseTestFixture( const CSC232BaseTestFixture & ) = delete;
        auto operator=( const CSC232BaseTestFixture & ) -> CSC232BaseTestFixture & = delete;
        CSC232BaseTestFixture( CSC232BaseTestFixture && ) = delete;
        auto operator=( CSC232BaseTestFixture && ) -> CSC232BaseTestFixture & = delete;

    protected:
        void SetUp( ) override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            // Redirect cout to our stringstream buffer or any other ostream
            sbuf = std::cout.rdbuf( );
            std::cout.rdbuf( buffer.rdbuf( ) );
            AdditionalSetup( );
        }

        void TearDown( ) override
        {
            // When done, redirect cout to its old self
            std::cout.rdbuf( sbuf );
            sbuf = nullptr;

            AdditionalTearDown( );
        }

        virtual void AdditionalSetup( )
        {
            /* template method for any customized additional setup */
        }

        virtual void AdditionalTearDown( )
        {
            /* template method for any customized additional setup */
        }

    private:
        // Reusable objects for each unit test in this test fixture and any of its children
        std::stringstream buffer{ std::stringstream{} };
        std::streambuf *sbuf{ nullptr };
        /*
         * With the above in place, you can now have tests on output statements
         * like this:
         *
         * <some function call or executable that inserts info into output stream...>
         * const std::string expected{ "1/1/1902\n" }; // what you expect to have been inserted
         * const std::string actual{ buffer.str( ) };  // what was actually inserted
         * EXPECT_EQ( expected, actual );
         */
    };
}

#endif
