cmake_minimum_required(VERSION 3.12)
project(BookService)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)
find_package(Threads REQUIRED)
find_package(nlohmann_json  REQUIRED)
find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)


add_executable(BookService src/main.cpp src/book.cpp)
target_link_libraries(BookService PkgConfig::Pistache Threads::Threads nlohmann_json::nlohmann_json)

add_subdirectory(test)

# Copy the test file to the build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/books.json ${CMAKE_CURRENT_BINARY_DIR}/books.json COPYONLY)

