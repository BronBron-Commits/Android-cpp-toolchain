# android-ndk.cmake
#
# This repository intentionally does NOT build using the Android NDK.
#
# Rationale:
# - Termux already provides:
#     - clang
#     - bionic
#     - native Android ABI
# - Using the NDK adds no value for on-device builds
# - Core infrastructure is owned by this repo, not Gradle/NDK
#
# Android apps are built by:
#   1. Compiling native binaries in Termux
#   2. Packaging them via a minimal Android loader (separate concern)
#
# This file exists only to prevent accidental use and confusion.

message(FATAL_ERROR
  "Android NDK builds are intentionally disabled in this repository.\n"
  "Use the Termux toolchain instead:\n"
  "  cmake --preset termux-debug\n"
)
