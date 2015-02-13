add_executable(gar gar_main.cpp gar.cpp lzs.cpp util.cpp)
target_link_libraries(gar ${Boost_LIBRARIES})

add_executable(lzs lzs_main.cpp lzs.cpp util.cpp)
target_link_libraries(lzs ${Boost_LIBRARIES})

add_executable(zar zar_main.cpp zar.cpp util.cpp)
target_link_libraries(zar ${Boost_LIBRARIES})