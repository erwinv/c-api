cmake_minimum_required(VERSION 3.5)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O3")

project(c-api LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MICROHTTPD REQUIRED IMPORTED_TARGET libmicrohttpd)
pkg_check_modules(JANSSON REQUIRED IMPORTED_TARGET jansson)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)

add_executable(c-api main.c server.c router.c controller.c respond.c jsonplaceholder-api.c)
set_property(TARGET c-api PROPERTY C_STANDARD 17)
target_link_libraries(c-api PUBLIC
    PkgConfig::MICROHTTPD
    PkgConfig::JANSSON
    PkgConfig::CURL)
