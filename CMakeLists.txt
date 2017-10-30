project (Neuron)
cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable (neuron neuron.cpp main_neuron.cpp network.cpp experiment.cpp)
add_executable (unittest neuron.cpp network.cpp test_neuron.cpp experiment.cpp)

target_link_libraries(unittest gtest gtest_main)
add_test(unittest unittest)
