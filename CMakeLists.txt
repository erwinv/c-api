cmake_minimum_required(VERSION 3.5)

project(c-api LANGUAGES C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MICROHTTPD REQUIRED IMPORTED_TARGET libmicrohttpd)
pkg_check_modules(JANSSON REQUIRED IMPORTED_TARGET jansson)

add_executable(c-api main.c server.c router.c controller.c respond.c)
set_property(TARGET c-api PROPERTY C_STANDARD 17)
target_link_libraries(c-api PUBLIC
    PkgConfig::MICROHTTPD
    PkgConfig::JANSSON)
