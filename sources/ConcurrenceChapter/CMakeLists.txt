CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

set(chapter1_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter1)
set(chapter2_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter2)
set(chapter3_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter3)
set(chapter4_root ${CMAKE_CURRENT_SOURCE_DIR}/Chapter4)
set(practice_root ${CMAKE_CURRENT_SOURCE_DIR}/Practice)

add_subdirectory(Chapter1)
add_subdirectory(Chapter2)
add_subdirectory(Chapter3)
add_subdirectory(Chapter4)
add_subdirectory(Practice)