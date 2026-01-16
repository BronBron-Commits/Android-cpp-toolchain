# APK Wrapper (Native Loader)

This directory contains a minimal Android APK wrapper whose only purpose is to
bootstrap a native C++ core.

Design principles:

- No Java/Kotlin app logic
- No engine code
- No simulation code
- No Android framework dependency beyond NativeActivity
- Core logic lives elsewhere and is loaded via dlopen()

Responsibilities:
- Create Android entry point
- Load libcore.so
- Transfer control

This loader is intentionally small, boring, and replaceable.
