add_executable(gar gar_main.cpp gar.cpp lzs.cpp util.cpp)
target_link_libraries(gar ${Boost_LIBRARIES})