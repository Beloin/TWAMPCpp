add_library(
        lib_impl STATIC
        utils/socket_utils.cpp
        ./utils/setup_logger.cpp
        ./network/server.cpp
        ./network/client.cpp
        ./network/messages.cpp
        network/connected_client.cpp
)

target_include_directories(lib_impl PRIVATE ../include)
target_include_directories(lib_impl PRIVATE .)