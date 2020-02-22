cmake_minimum_required(VERSION 2.4)

project(imi)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS} ${LIB_BSD})
set(LIB_BSD_FILE /usr/lib/libbsd.so)

add_executable(imi
   src/imi.c
   src/worddef.c
   src/defmenu.c
   src/parse.c
)

target_compile_options(imi PRIVATE -Wall -Wextra -pedantic -lbsd)
target_link_libraries(imi ${CURSES_LIBRARIES} ${LIB_BSD_FILE}) 
