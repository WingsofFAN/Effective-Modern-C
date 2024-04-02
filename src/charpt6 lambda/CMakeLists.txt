cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 20)

set(Deducing_Type_List  "31" "32" "33" "34")
foreach(_per_code ${Deducing_Type_List})
    # add the executable
    add_executable(${_per_code} ${_per_code}.cpp)
    target_link_libraries(${_per_code} ${Boost_LIBRARIES} pthread)

endforeach()

