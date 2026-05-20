cmake_minimum_required(VERSION 3.29)
project(ak_redis)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG asio-1-38-0
)

FetchContent_MakeAvailable(asio)

find_package(Threads REQUIRED)

# Server binary
add_executable(ak_redis_server
        server/server.cpp
        server/main.cpp)

target_include_directories(ak_redis_server PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_compile_definitions(ak_redis_server PRIVATE ASIO_STANDALONE)

target_link_libraries(ak_redis_server PRIVATE Threads::Threads)

# Client binary
add_executable(ak_redis_client
        client/client.cpp
        client/main.cpp)

target_include_directories(ak_redis_client PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_compile_definitions(ak_redis_client PRIVATE ASIO_STANDALONE)

target_link_libraries(ak_redis_client PRIVATE Threads::Threads)

if(WIN32)
    target_link_libraries(ak_redis_server PRIVATE
            ws2_32
            wsock32
    )
    target_link_libraries(ak_redis_client PRIVATE
            ws2_32
            wsock32
    )
endif ()

if (MSVC)
    target_compile_options(ak_redis_server PRIVATE /W4)
    target_compile_options(ak_redis_client PRIVATE /W4)
else ()
    target_compile_options(ak_redis_server PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

    target_compile_options(ak_redis_client PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif ()