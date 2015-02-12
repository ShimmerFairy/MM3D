cmake_minimum_required(VERSION 2.8)

project(garextract)

# fun fact: Boost is an interdependent mess of libraries
# fun fact: FindBoost apparently does not know this
# fun fact: I shouldn't have to put this ↓↓↓↓↓↓ in manually.
find_package(Boost COMPONENTS filesystem system)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

include_directories(include ${Boost_INCLUDE_DIRS})

add_subdirectory(src)
