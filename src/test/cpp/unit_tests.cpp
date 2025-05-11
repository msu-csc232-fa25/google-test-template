
/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2025
 *
 * @file      unit_tests.cpp
 * @authors   Jim Daehn <jdaehn@missouristate.edu>
 * @brief     Google Test implementation template.
 */

#include "csc232.h"
#include "gtest/gtest.h"

/**
 * @brief Namespace to encapsulate course specific macros, declarations and definitions.
 */
namespace csc232
{
    static int possiblePoints{0};
    static int earnedPoints{0};
    static const int MAX_CORRECTNESS_PTS{2};

    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test
    {
    public:
        CSC232BaseTestFixture() : buffer{std::stringstream{}}

        {
            // Intentionally empty; attributes initialized above.
        }

        CSC232BaseTestFixture(const CSC232BaseTestFixture &) = delete;
        auto operator=(const CSC232BaseTestFixture &) -> CSC232BaseTestFixture & = delete;
        CSC232BaseTestFixture(CSC232BaseTestFixture &&) = delete;
        auto operator=(CSC232BaseTestFixture &&) -> CSC232BaseTestFixture & = delete;

        ~CSC232BaseTestFixture() override = default;

    protected:
        void SetUp() override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            // Redirect cout to our stringstream buffer or any other ostream
            sbuf = std::cout.rdbuf();
            std::cout.rdbuf(buffer.rdbuf());

            AdditionalSetup();

            if (const ::testing::TestInfo *test_info = ::testing::UnitTest::GetInstance()->current_test_info())
            {
                const char *test_name = test_info->name();
                // Ignore tests in this base fixture
                if (strcmp(test_info->test_suite_name(), "CSC232BaseTestFixture") != 0)
                {
                    // Only accumulate points for their work
                    const auto bootstrap = "Bootstrap";
                    if (strcmp(test_name, bootstrap) != 0)
                    {
                        possiblePoints += 1;
                    }
                }
            }
        }

        void TearDown() override
        {
            // When done, redirect cout to its old self
            std::cout.rdbuf(sbuf);
            sbuf = nullptr;

            AdditionalTearDown();

            if (!HasFailure())
            {
                if (const ::testing::TestInfo *test_info = ::testing::UnitTest::GetInstance()->current_test_info())
                {
                    const char *test_name = test_info->name();
                    // Ignore tests in this base fixture
                    if (strcmp(test_info->test_suite_name(), "CSC232BaseTestFixture") != 0)
                    {
                        // Only accumulate points for their work
                        if (const auto bootstrap = "Bootstrap"; strcmp(test_name, bootstrap) != 0)
                        {
                            earnedPoints += 1;
                        }
                    }
                }
            }
        }

        virtual void AdditionalSetup()
        {
            /* template method for any customized additional setup */
        }

        virtual void AdditionalTearDown()
        {
            /* template method for any customized additional setup */
        }

    private:
        // Reusable objects for each unit test in this test fixture and any of its children
        std::stringstream buffer;
        std::streambuf *sbuf{nullptr};
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

    class Task1TestFixture : public CSC232BaseTestFixture
    {
    };

#if TEST_TASK1
    TEST_F(Task1TestFixture, RewriteThisTest)
    {
        std::cout << "Task 1 is ready for evaluation, but this isn't going to validate anything.\n";
        SUCCEED();
    }
#else
    TEST_F(Task1TestFixture, ItIsNotReady)
    {
        std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
        FAIL();
    }
#endif

    class Task2TestFixture : public CSC232BaseTestFixture
    {
    };

#if TEST_TASK2
    TEST_F(Task2TestFixture, RewriteThisTest)
    {
        std::cout << "Task 2 is ready for evaluation, but this isn't going to validate anything.\n";
        FAIL();
    }
#else
    TEST_F(Task2TestFixture, ItIsNotReady)
    {
        std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
        FAIL();
    }
#endif

    class Task3TestFixture : public CSC232BaseTestFixture
    {
    };
#if TEST_TASK3
    TEST_F(Task3TestFixture, RewriteThisTest)
    {
        std::cout << "Task 3 is ready for evaluation, but this isn't going to validate anything.\n";
        FAIL();
    }
#else
    TEST_F(Task3TestFixture, ItIsNotReady)
    {
        std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
        FAIL();
    }
#endif

    class Task4TestFixture : public CSC232BaseTestFixture
    {
    };
#if TEST_TASK4
    TEST_F(Task4TestFixture, RewriteThisTest)
    {
        std::cout << "Task 4 is ready for evaluation, but this isn't going to validate anything.\n";
        FAIL();
    }
#else
    TEST_F(Task4TestFixture, ItIsNotReady)
    {
        std::cerr << "Task 4 is not ready for evaluation; please toggle the TEST_TASK4 macro to TRUE\n";
        FAIL();
    }
#endif

    class Task5TestFixture : public CSC232BaseTestFixture
    {
    };
#if TEST_TASK5
    TEST_F(Task5TestFixture, RewriteThisTest)
    {
        std::cout << "Task 5 is ready for evaluation, but this isn't going to validate anything.\n";
        FAIL();
    }
#else
    TEST_F(Task5TestFixture, ItIsNotReady)
    {
        std::cerr << "Task 5 is not ready for evaluation; please toggle the TEST_TASK5 macro to TRUE\n";
        FAIL();
    }
#endif
} // end namespace

auto main(int argc, char **argv) -> int
{
    constexpr int POINTS_HEADER_COLUMN_WIDTH{21};
    constexpr int POINTS_VALUE_COLUMN_WIDTH{5};
    constexpr int FLOAT_PRECISION{2};

    ::testing::InitGoogleTest(&argc, argv);
    const int result{RUN_ALL_TESTS()};

    std::cout << std::fixed << std::setprecision(FLOAT_PRECISION);
    std::cout << "\n\n";
    std::cout << std::left << std::setw(POINTS_HEADER_COLUMN_WIDTH) << "Earned Points:"
        << std::right << std::setw(POINTS_VALUE_COLUMN_WIDTH) << static_cast<double>(csc232::earnedPoints) << std::endl;
    std::cout << std::left << std::setw(POINTS_HEADER_COLUMN_WIDTH) << "Possible Points:"
        << std::right << std::setw(POINTS_VALUE_COLUMN_WIDTH) << static_cast<double>(csc232::possiblePoints) << std::endl;
    double percentCorrect{static_cast<double>(csc232::earnedPoints) / csc232::possiblePoints};
    double correctnessPoints{csc232::possiblePoints != 0
                                 ? percentCorrect * csc232::MAX_CORRECTNESS_PTS
                                 : 0};
    std::cout << std::left << std::setw(POINTS_HEADER_COLUMN_WIDTH) << "Correctness Points:"
        << std::right << std::setw(POINTS_VALUE_COLUMN_WIDTH) << correctnessPoints << std::endl;
    return result;
}
