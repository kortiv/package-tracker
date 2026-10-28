cmake_minimum_required(VERSION 3.20)

project(package_tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_executable(package_tracker
    src/frameworks_drivers/main.cpp
    src/interface_adapters/in_memory_package_gateway.cpp
)

target_include_directories(package_tracker
    PRIVATE
        src
)

add_executable(package_tracker_round_trip_test
    tests/round_trip_test.cpp
    src/interface_adapters/in_memory_package_gateway.cpp
)

target_include_directories(package_tracker_round_trip_test
    PRIVATE
        src
)

add_test(NAME package_tracker_round_trip_test COMMAND package_tracker_round_trip_test)
