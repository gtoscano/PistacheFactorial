# Find the GTest package
find_package(GTest REQUIRED)
find_package(cpr REQUIRED)


# Add the executable test
add_executable(BookServiceTest book_service_test.cpp)

# Include the header files from the 'include' directory
target_include_directories(BookServiceTest PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the test executable with the necessary libraries
target_link_libraries(BookServiceTest GTest::GTest GTest::Main Threads::Threads nlohmann_json::nlohmann_json cpr::cpr)

# Enable testing
enable_testing()

# Add the test
add_test(NAME BookServiceTest COMMAND BookServiceTest)

