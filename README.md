# Android C++ Toolchain

Modern, CMake-first toolchain and build presets for cross-compiling high-performance C/C++ code to Android (native libraries, executables, JNI modules, etc.).

This repository provides:
- Pre-configured CMake toolchain files for Android NDK (Clang-based)
- Ready-to-use CMakePresets.json for common build scenarios (debug/release, multiple ABIs: armeabi-v7a, arm64-v8a, x86_64, x86)
- Helper scripts/structure for standalone toolchain usage or integration into larger projects
- Clean separation of source, headers, and build logic

Designed for developers who want reliable, reproducible Android native builds without fighting NDK setup every time.

## Features

- **CMake Presets** — one-command configuration for different ABIs, build types, and API levels
- **Toolchain files** — robust Android-Clang toolchain definitions (in `toolchains/`)
- **Minimal boilerplate** — drop-in support for new projects or submodules
- **Supports latest NDK practices** — position-independent code, modern C++ standards, LTO if desired
- **Optional APK wrapper** — utilities in `apk-wrapper/` to help package native libs into APKs (coming soon / WIP)

## Requirements

- CMake 3.21+
- Android NDK r25+ (r26+ recommended)
- Android SDK (for final APK packaging if using apk-wrapper)
- Clang (comes with NDK)

## Quick Start

1. Clone this repo (or add as submodule):
   ```bash
   git clone https://github.com/BronBron-Commits/Android-cpp-toolchain.git
   # or
   git submodule add https://github.com/BronBron-Commits/Android-cpp-toolchain extern/android-toolchain
   ```

2. Use one of the presets:
   ```bash
   cmake --preset android-arm64-release
   cmake --build --preset android-arm64-release
   ```

   Available presets (see `CMakePresets.json` for full list):
   - `android-arm64-debug`
   - `android-arm64-release`
   - `android-armeabi-v7a-release`
   - `android-x86_64-release`
   - etc.

3. (Optional) Point your own project to this toolchain:
   ```cmake
   # In your top-level CMakeLists.txt
   set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/extern/android-toolchain/toolchains/android.toolchain.cmake")
   ```

## Project Structure

```
.
├── CMakeLists.txt          # Example / root CMake file (minimal)
├── CMakePresets.json       # All preset configurations
├── toolchains/             # Android toolchain .cmake files
├── include/                # Public headers (if providing a library)
├── src/                    # Source code / examples
├── apk-wrapper/            # Helpers for JNI → APK integration (WIP)
└── .gitignore
```

## Customization

Edit `CMakePresets.json` to adjust:
- `ANDROID_PLATFORM` (android-21 → android-34, etc.)
- `ANDROID_ABI`
- `ANDROID_STL` (c++_shared, c++_static, etc.)
- Optimization flags, sani
