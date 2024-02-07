add_library(
        lib_impl STATIC
        utils/socket_utils.cpp
        ./utils/setup_logger.cpp
        ./network/server.cpp
        ./network/client.cpp
        ./network/messages.cpp
        network/connected_client_worker.cpp
        utils/time_utils.cpp
        network/test_sessions/test_session.cpp network/test_sessions/test_session.h)

target_include_directories(lib_impl PRIVATE ../include)
target_include_directories(lib_impl PRIVATE .)