cmake_minimum_required(VERSION 3.20)

project(Missile LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)

add_executable(Missile 
main.cpp
render.cpp
)

find_package(Eigen3 REQUIRED)

find_package(spdlog REQUIRED)

target_link_libraries(Missile PRIVATE
 Eigen3::Eigen
 spdlog::spdlog)