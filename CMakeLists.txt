set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.27)

project(DSA
  DESCRIPTION "My DSA Implementations"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a library, containing only .h, i.e. an interface library
add_library(sorting INTERFACE)
target_include_directories(sorting INTERFACE include/sorting)

add_library(searching INTERFACE include/searching)
target_include_directories(searching INTERFACE include/searching)

# Add a library, containing only both .h and .cpp, i.e. a static library
add_library(vector STATIC src/vector/Vector.cpp include/vector/Vector.h)
target_include_directories(vector PUBLIC include)

add_library(list INTERFACE)
target_include_directories(list INTERFACE include/list)

add_library(tree INTERFACE)
target_include_directories(tree INTERFACE include/tree)

# Add Tests
add_subdirectory(tests)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC sorting)
target_link_libraries(main PUBLIC searching)
target_link_libraries(main PUBLIC vector)
target_link_libraries(main PUBLIC list)
target_link_libraries(main PUBLIC tree)

