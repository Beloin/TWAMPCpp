cmake_minimum_required(VERSION 3.24)
project(twamp)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        twamp
        src/main.cpp
)

target_include_directories(twamp PRIVATE ./include/)
target_include_directories(twamp PRIVATE lib/)

add_compile_definitions(SPDLOG_DEBUG_ON)

add_subdirectory(lib)
target_link_libraries(twamp PRIVATE lib_impl)

# spdlog lib package and headers
find_package(spdlog REQUIRED)
target_link_libraries(twamp PRIVATE spdlog::spdlog_header_only)
#target_link_libraries(lcd_dht11 PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)


