CMAKE_MINIMUM_REQUIRED(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(blinky)

target_sources(app PRIVATE src/main.c)
