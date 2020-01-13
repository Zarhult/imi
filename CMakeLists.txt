cmake_minimum_required(VERSION 2.4)

project(imi)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(imi
   src/imi.c
   src/menu.c
   src/menuarray.c
)

if(MSVC)
    target_compile_options(imi PRIVATE /W4 /WX)
else()
    target_compile_options(imi PRIVATE -Wall -Wextra -pedantic)
endif()

target_link_libraries(imi ${CURSES_LIBRARIES}) 
