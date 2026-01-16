cmake_minimum_required(VERSION 3.22)

project(android_cpp_toolchain
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ANDROID_DETERMINISTIC "Enable deterministic-friendly build flags" ON)

if (ANDROID_DETERMINISTIC)
    add_compile_options(
        -fno-fast-math
        -ffp-model=precise
        -fno-strict-aliasing
    )
endif()

add_library(core SHARED
    src/core.cpp
    src/core_loop.cpp
    src/core_input.cpp
    src/core_lifecycle.cpp
    src/example_state.cpp
    src/android_core_entry.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core PRIVATE log)

add_executable(smoke src/smoke.cpp)
target_link_libraries(smoke PRIVATE core)
