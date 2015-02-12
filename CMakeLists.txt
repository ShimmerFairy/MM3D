cmake_minimum_required(VERSION 2.8)

project(garextract)

# fun fact: Boost is an interdependent mess of libraries
# fun fact: FindBoost apparently does not know this
# fun fact: I shouldn't have to put this ↓↓↓↓↓↓ in manually.
find_package(Boost COMPONENTS filesystem system)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11")

include_directories(include ${Boost_INCLUDE_DIRS})

add_subdirectory(src)