cmake_minimum_required(VERSION 3.15)


set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS regex system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")
endif()

set(Deducing_Type_List "01" "02" "03" "04")
foreach(_per_code ${Deducing_Type_List})
    # add the executable
    add_executable(${_per_code} ${_per_code}.cpp)
    target_link_libraries(${_per_code} ${Boost_LIBRARIES})
endforeach()