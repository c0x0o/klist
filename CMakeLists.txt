project(LIST)

cmake_minimum_required(VERSION 2.8.0)

include_directories(src)

set(CMAKE_BUILD_TYPE Debug)
set(libsource ./src/list.c)
set(testsource ./examples/examples.c)

add_executable(tester ${libsource} ${testsource})
add_library(klist STATIC ${libsource})
