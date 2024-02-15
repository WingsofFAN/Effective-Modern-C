cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 20)

set(Deducing_Type_List "05" "06")
foreach(_per_code ${Deducing_Type_List})
    # add the executable
    add_executable(${_per_code} ${_per_code}.cpp)
endforeach()