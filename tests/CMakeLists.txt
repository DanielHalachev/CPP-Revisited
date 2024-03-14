# Let's ensure Catch2 is available
find_package(Catch2 REQUIRED)

# Automatically enable catch2 to generate a main (catch2 v2.9.0+)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

# Gather all test files.
file(GLOB_RECURSE TEST_LIST LIST_DIRECTORIES false *.cpp)

# Create a test target with the collected source files
add_executable(tests ${TEST_LIST})

# Link the necessary libraries
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain sorting searching vector)

# Automatically discover tests that are defined in catch based test files
catch_discover_tests(tests)

