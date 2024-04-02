cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 20)

set(Deducing_Type_List  "23" "24" "25" "26" "27" "28" "29" "30")
foreach(_per_code ${Deducing_Type_List})
    # add the executable
    add_executable(${_per_code} ${_per_code}.cpp)
    target_link_libraries(${_per_code} ${Boost_LIBRARIES} pthread)

endforeach()

