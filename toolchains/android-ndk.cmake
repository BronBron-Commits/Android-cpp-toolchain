# Android NDK LLVM toolchain
# Host: desktop Linux / macOS / Windows
# Target: Android
# NOT supported on Android / Termux host

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Android")
    message(FATAL_ERROR
        "Android NDK cannot be used on Android hosts.\n"
        "Use the Termux toolchain instead:\n"
        "  --preset termux-debug\n"
    )
endif()

if (NOT DEFINED ENV{ANDROID_NDK})
    message(FATAL_ERROR "ANDROID_NDK environment variable not set")
endif()

set(ANDROID_NDK $ENV{ANDROID_NDK})

set(ANDROID_ABI arm64-v8a)
set(ANDROID_API 24)

# Host detection (desktop only)
if (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(NDK_HOST_TAG linux-x86_64)
elseif (CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
    set(NDK_HOST_TAG darwin-arm64)
else()
    message(FATAL_ERROR "Unsupported NDK host architecture")
endif()

set(LLVM_BIN ${ANDROID_NDK}/toolchains/llvm/prebuilt/${NDK_HOST_TAG}/bin)

set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION ${ANDROID_API})
set(CMAKE_ANDROID_ARCH_ABI ${ANDROID_ABI})
set(CMAKE_ANDROID_NDK ${ANDROID_NDK})
set(CMAKE_ANDROID_API ${ANDROID_API})
set(CMAKE_ANDROID_STL_TYPE c++_static)

set(CMAKE_C_COMPILER   ${LLVM_BIN}/aarch64-linux-android${ANDROID_API}-clang)
set(CMAKE_CXX_COMPILER ${LLVM_BIN}/aarch64-linux-android${ANDROID_API}-clang++)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -fno-fast-math
    -ffp-model=precise
    -fno-strict-aliasing
)

message(STATUS "Using Android NDK at: ${ANDROID_NDK}")
message(STATUS "NDK host tag: ${NDK_HOST_TAG}")
message(STATUS "ABI: ${ANDROID_ABI}")
message(STATUS "API level: ${ANDROID_API}")
