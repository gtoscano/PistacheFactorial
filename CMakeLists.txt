cmake_minimum_required(VERSION 3.12)
project(PistacheFactorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(Threads REQUIRED)
find_package(nlohmann_json  REQUIRED)
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


add_executable(PistacheFactorial src/main.cpp src/factorial.cpp)
target_link_libraries(PistacheFactorial PkgConfig::Pistache Threads::Threads nlohmann_json::nlohmann_json)

#add_subdirectory(test)


