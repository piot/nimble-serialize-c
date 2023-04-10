cmake_minimum_required(VERSION 3.17)
project(nimble_serialize C)

set(CMAKE_C_STANDARD 11)

if (DEFINED PLATFORM)
    message("platform ${PLATFORM}")
    if (PLATFORM STREQUAL "OS64" )
        add_compile_definitions(TORNADO_OS_IOS)
        set(OS_IOS 1)
        set(OS_NAME "ios")
    endif()
elseif (APPLE)
    add_compile_definitions(TORNADO_OS_MACOS)
    set(OS_MACOS 1)
    set(OS_NAME "macos")
elseif (UNIX)
    add_compile_definitions(TORNADO_OS_LINUX)
    set(OS_LINUX 1)
    set(OS_NAME "linux")

elseif (WIN32)
    add_compile_definitions(TORNADO_OS_WINDOWS)
    set(OS_WINDOWS 1)
    set(OS_NAME "windows")
endif()


if (isDebug)
    message("Debug build detected")
    add_compile_definitions(CONFIGURATION_DEBUG TYRAN_CONFIGURATION_DEBUG)
    set(CONFIGURATION_DEBUG 1)
endif()


set(deps ../../deps/)

file(GLOB_RECURSE lib_src FOLLOW_SYMLINKS
        "*.c"
        )

add_library(nimble_serialize
    ${lib_src}
)

target_include_directories(nimble_serialize PUBLIC ${deps}piot/clog/src/include)
target_include_directories(nimble_serialize PUBLIC ${deps}piot/tiny-libc/src/include)
target_include_directories(nimble_serialize PUBLIC ${deps}piot/flood-c/src/include)
target_include_directories(nimble_serialize PUBLIC ${deps}piot/blob-stream/src/include)
target_include_directories(nimble_serialize PUBLIC ${deps}piot/bit-array/src/include)
target_include_directories(nimble_serialize PUBLIC ${deps}piot/monotonic-time-c/src/include)
target_include_directories(nimble_serialize PUBLIC ../include)


