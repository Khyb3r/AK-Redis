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

add_executable(ak_redis src/main.cpp)

target_include_directories(ak_redis PRIVATE ${asio_SOURCE_DIR}/asio/include)

target_compile_definitions(ak_redis PRIVATE ASIO_STANDALONE)

find_package(Threads REQUIRED)
target_link_libraries(ak_redis PRIVATE Threads::Threads)

if(WIN32)
    target_link_libraries(ak_redis PRIVATE
            ws2_32
            wsock32
    )
endif ()

if (MSVC)
    target_compile_options(ak_redis PRIVATE /W4)
else ()
    target_compile_options(ak_redis PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif ()