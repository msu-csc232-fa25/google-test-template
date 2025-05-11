cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,bugprone-*,clang-analyzer-*,cppcoreguidelines-*,modernize-*,readability-*)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(lab-or-hw)

if (CMAKE_VERSION GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif ()

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

# Source sets for targets
set(SRC_MAIN_FILES src/main/cpp/main.cpp)
set(SRC_DEMO_FILES src/main/cpp/demo.cpp)
set(SRC_UNIT_TEST_FILES src/test/cpp/unit_tests.cpp)

# Setup Google Test
set(GOOGLE_TEST_ARCHIVE "v1.14.0")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/${GOOGLE_TEST_ARCHIVE}.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(main ${SRC_MAIN_FILES})
add_executable(demo ${SRC_DEMO_FILES})
add_executable(unit_tests ${SRC_UNIT_TEST_FILES})

# Now simply link against gtest or gtest_main as needed.
target_link_libraries(unit_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_tests)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)
target_include_directories(unit_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include ${CMAKE_CURRENT_LIST_DIR}/src/main/cpp)

# add custom commands that copy data input files to target working directories
add_custom_command(TARGET main POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/main_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET demo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/demo_data.txt ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(TARGET unit_tests POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test/resources/test_data.txt ${CMAKE_CURRENT_BINARY_DIR})

# first we can indicate the documentation build as an option and set it to OFF by default
option(BUILD_DOC "Build documentation" OFF)
find_package(Doxygen
        OPTIONAL_COMPONENTS dot mscgen dia)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/config/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the config together with the application
    add_custom_target(doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
