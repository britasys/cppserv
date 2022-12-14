cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

option(APP_BUILD_SAMPLES "build samples" OFF)
option(APP_BUILD_TESTS "build tests" OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# FetchContent
include(FetchContent)

# boost
find_package(Boost 1.78.0 REQUIRED)

# app directories
set(APP_TESTS_DIR ./tests)
set(APP_SAMPLES_DIR ./samples)

# project include directories
set(APP_INCLUDE_DIRS ./include)

# build tests
if (APP_BUILD_TESTS)

    # googletest
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(googletest)

    set(TEST_PROJECTS gtests)
    foreach(TEST_PROJECT ${TEST_PROJECTS})
        project(${TEST_PROJECT} VERSION 1.0)
        add_compile_options(
            $<$<CONFIG:>:/MT>
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
        add_executable(${TEST_PROJECT} ${APP_TESTS_DIR}/${TEST_PROJECT}.cpp)
        target_link_directories(${TEST_PROJECT} PRIVATE ${CMAKE_BINARY_DIR}/lib)
        target_include_directories(${TEST_PROJECT} PRIVATE ${APP_INCLUDE_DIRS})
        target_link_libraries(${TEST_PROJECT} GTest::gtest_main)
        include(GoogleTest)
        gtest_discover_tests(${TEST_PROJECT})
    endforeach()
endif(APP_BUILD_TESTS)

# build samples
if (APP_BUILD_SAMPLES)
    
    set(SAMPLE_PROJECTS cppserv_sample)
    foreach(SAMPLE_PROJECT ${SAMPLE_PROJECTS})
        project(${SAMPLE_PROJECT} VERSION 1.0)
        add_compile_options(
            $<$<CONFIG:>:/MT>
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
        add_executable(${SAMPLE_PROJECT} ${APP_SAMPLES_DIR}/${SAMPLE_PROJECT}.cpp)
        target_include_directories(${SAMPLE_PROJECT} PRIVATE ${APP_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
        target_link_directories(${SAMPLE_PROJECT} PRIVATE ${CMAKE_BINARY_DIR}/lib)
    endforeach()
endif(APP_BUILD_SAMPLES)