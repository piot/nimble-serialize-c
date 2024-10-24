# Copyright (c) Peter Bjorklund. All rights reserved.

macro(set_local_and_parent NAME VALUE)
  set(${NAME} ${VALUE})
  set(${NAME}
      ${VALUE}
      PARENT_SCOPE)
endmacro()

function(set_tornado targetName)
  target_compile_features(${targetName} PUBLIC c_std_99)
  set_local_and_parent(CMAKE_C_EXTENSIONS false)

  # --- Detect CMake build type, compiler and operating system ---

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("detected debug build")
    set_local_and_parent(isDebug TRUE)
  else()
    message("detected release build")
    set_local_and_parent(isDebug FALSE)
  endif()

  if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    set_local_and_parent(COMPILER_NAME "clang")
    set_local_and_parent(COMPILER_CLANG TRUE)
  elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set_local_and_parent(COMPILER_NAME "gcc")
    set_local_and_parent(COMPILER_GCC TRUE)
  elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set_local_and_parent(COMPILER_NAME "msvc")
    set_local_and_parent(COMPILER_MSVC TRUE)
  endif()

  message("detected compiler: '${CMAKE_C_COMPILER_ID}' (${COMPILER_NAME})")

  set(useSanitizers false)

  if(useSanitizers)
    message("using sanitizers")
    set(sanitizers "-fsanitize=address")
  endif()

  if(APPLE)
    set_local_and_parent(OS_MACOS TRUE)
    set_local_and_parent(OS_NAME macos)
  elseif(UNIX)
    set_local_and_parent(OS_LINUX TRUE)
    set_local_and_parent(OS_NAME linux)
  elseif(WIN32)
    set_local_and_parent(OS_WINDOWS TRUE)
    set_local_and_parent(OS_NAME windows)
  endif()
  string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} PROCESSOR)
  set_local_and_parent(CPU_ARCHITECTURE ${PROCESSOR})

  # ----- Set Compile options depending on compiler

  if(COMPILER_CLANG)
    target_compile_options(
      ${targetName}
      PRIVATE -Weverything
              -Werror
              -Wno-padded # the order of the fields in struct can matter (ABI)
              -Wno-unsafe-buffer-usage # unclear why it fails on clang-16
              -Wno-unknown-warning-option # support newer clang versions, e.g.
                                          # clang-16
              -Wno-declaration-after-statement # bug in clang, should be legal
                                               # for std c99
              -Wno-switch-enum # if there is a explicit default case, then it
              # should not be reported as an error

              -Wno-switch-default # new clang is strange, even if all values are covered in a
                                  # switch, it still complains
              ${sanitizers})
  elseif(COMPILER_GCC)
    target_compile_options(
      ${targetName}
      PRIVATE -Wall
              -Wextra
              -Wpedantic
              -Werror
              -Wno-padded # the order of the fields in struct can matter (ABI)
              ${sanitizers})
  elseif(COMPILER_MSVC)
    target_compile_options(
      ${targetName}
      PRIVATE /Wall
              /WX
              /wd4820 # bytes padding added after data member
              /wd4668 # bug in winioctl.h (is not defined as a preprocessor
                      # macro, replacing with '0' for '#if/#elif')
              /wd5045 # Compiler will insert Spectre mitigation for memory load
                      # if /Qspectre switch specified
              /wd4005 # Bug in ntstatus.h (macro redefinition)
    )
  else()
    target_compile_options(${targetName} PRIVATE -Wall)
  endif()

  if(EMSCRIPTEN)
    message("Emscripten detected!")
    target_compile_options(
      ${targetName}
      PRIVATE -Wno-switch-default # emscripten is probably using an old compiler
                                  # version, even if all values are covered in a
                                  # switch, it still complains
              -Wno-disabled-macro-expansion # bug in emscripten compiler?
              -Wno-poison-system-directories # might be bug in emscripten
                                             # compiler?
    )
  endif()

  if(NOT isDebug)
    message("optimize!")
    target_compile_options(${targetName} PRIVATE -O3)
  endif()

  # ----- Set Compile Definitions based on build type and operating system

  if(OS_MACOS)
    message("MacOS detected!")
    target_compile_definitions(${targetName} PRIVATE TORNADO_OS_MACOS)
  elseif(OS_LINUX)
    message("Linux Detected!")
    target_compile_definitions(${targetName} PRIVATE TORNADO_OS_LINUX)
  elseif(OS_WINDOWS)
    message("Windows detected!")
    target_compile_definitions(${targetName} PRIVATE TORNADO_OS_WINDOWS)
  endif()

  if(isDebug)
    message("Setting definitions based on debug")
    target_compile_definitions(${targetName} PRIVATE CONFIGURATION_DEBUG)
  endif()

endfunction()
