cmake_minimum_required(VERSION 3.16.3)
project(nimble-serialize C)
enable_testing()

add_subdirectory(deps/piot/clog/src/lib)
add_subdirectory(deps/piot/flood-c/src/lib)
add_subdirectory(deps/piot/tiny-libc/src/lib)


add_subdirectory(src)
