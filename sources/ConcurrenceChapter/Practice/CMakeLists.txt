CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(Practice)

add_definitions(-DPRACTICE_LIB)

file(GLOB inc_files "./inc/*.h")
source_group("inc" FILES ${inc_files})

file(GLOB src_files "./src/*.cpp")
source_group("src" FILES ${src_files})

include_directories(
    inc
    inc_func_files
)

add_library(${PROJECT_NAME}
    SHARED
    ${inc_files}
    ${src_files}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${cc_exe_dir}
    LIBRARY_OUTPUT_DIRECTORY ${cc_exe_dir}
    RUNTIME_OUTPUT_DIRECTORY ${cc_exe_dir}
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "ConcurreceChapter")