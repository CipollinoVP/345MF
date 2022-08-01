cmake_minimum_required(VERSION 3.3)
project(345MF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")


set(SOURCE_FILES main.cpp LoginApp.h SecurityApp.h DirectorApp.h SysAdminApp.h postgres.h)
add_executable(345MF ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
find_package(PostgreSQL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(345MF PRIVATE ${PostgreSQL_LIBRARIES} ${GTK3_LIBRARIES} ${OpenCV_LIBS})

target_include_directories(345MF PRIVATE ${PostgreSQL_INCLUDE_DIRS})