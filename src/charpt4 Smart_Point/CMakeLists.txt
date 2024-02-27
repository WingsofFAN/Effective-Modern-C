cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 20)

set(Deducing_Type_List  "18" "19" "20" "21")
foreach(_per_code ${Deducing_Type_List})
    # add the executable
    add_executable(${_per_code} ${_per_code}.cpp)
    target_link_libraries(${_per_code} ${Boost_LIBRARIES} pthread)

endforeach()


add_executable(22a 22.cpp 22A.cpp)
add_executable(22b 22.cpp 22B.cpp)