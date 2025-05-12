
/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file      test_task2.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#include "base_test_fixture.h"
#include "csc232.h"
#include "gtest/gtest.h"

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
#if TEST_TASK2
    class Task2TestFixture : public CSC232BaseTestFixture
    {
    };

    TEST_F( Task2TestFixture, RewriteThisTest )
    {
        std::cout << "Task 2 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED( );
    }
#else
    TEST( Task2TestSuite, ItIsNotReady )
    {
        std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
        ADD_FAILURE_AT( "include/csc232.h", 22 );
    }
#endif // TEST_TASK2

} // end namespace
