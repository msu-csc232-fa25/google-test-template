/**
 * CSC232 - Data Structures
 * Missouri State University, Fall 2025
 *
 * @file      base_test_fixture.h
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation base test fixture.
 */

#ifndef CSC232_BASE_TEST_FIXTURE_H
#define CSC232_BASE_TEST_FIXTURE_H

#include "csc232.h"
#include "gtest/gtest.h"

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test
    {
    public:
        /**
         * Default constructor.
         */
        CSC232BaseTestFixture( ) = default;

        /**
         * Default virtual destructor.
         */
        virtual ~CSC232BaseTestFixture( ) override = default;

        /**
         * Deleted copy constructor.
         */
        CSC232BaseTestFixture( const CSC232BaseTestFixture & ) = delete;

        /**
         * Deleted copy assignment operator.
         */
        auto operator=( const CSC232BaseTestFixture & ) -> CSC232BaseTestFixture & = delete;

        /**
         * Deleted move constructor.
         */
        CSC232BaseTestFixture( CSC232BaseTestFixture && ) = delete;

        /**
         * Deleted move assignment operator.
         */
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
