cmake_minimum_required(VERSION 3.8)

set (cpp_concurrence CppConcurrence_${CMAKE_BUILD_TYPE}_${CC_PLATFORM})
project(${cpp_concurrence})

#Set third libs directories
set (cc_root_dir ${PROJECT_SOURCE_DIR})
set (cc_3rdlibs_dir ${cc_root_dir}/CppConcurrence_3rd)
#Set project ext output path
set (cc_lib_dir ${cc_root_dir}/output/lib/${CC_PLATFORM})
set (cc_exe_dir ${cc_root_dir}/output/exe/${CC_PLATFORM})
set (cc_resource_dir ${cc_root_dir}/resources)

set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ConcurrenceModule)

##default all project include ${PROJECT_SOURCE_DIR}
include_directories(${cc_root_dir})
## default all project link incude under directories
link_directories(${cc_lib_dir})
link_directories(${cc_exe_dir})

## 3rdlibs path variables definitions
include("${cc_root_dir}/cmake/ThirdLibsPaths.cmake")

add_subdirectory(${cc_root_dir}/sources)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

