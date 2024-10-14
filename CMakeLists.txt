cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0100 NEW)

project(DameGameBoy VERSION 6.0.0 LANGUAGES CXX)

message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
message(PROJECT_VERSION="${CMAKE_PROJECT_VERSION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Gui Core)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(src)
