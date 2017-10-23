project (Neuron)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron neuron2.cpp main_neuron2.cpp network.cpp)
add_executable (unittest neuron2.cpp test_neuron.cpp)

target_link_libraries(unittest gtest gtest_main)
add_test(unittest unittest)
