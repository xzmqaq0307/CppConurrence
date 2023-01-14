CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(chapter1_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter1)
set(chapter1_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter2)

add_subdirectory(Chapter1)
add_subdirectory(Chapter2)
