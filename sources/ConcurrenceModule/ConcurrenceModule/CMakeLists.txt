#CMake version requirements
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(ConcurrenceModule)

# add_Definitions(-DZWAIMODULE_TESTER)
add_Definitions(-DCONCURRENCE_TESTER)

file(GLOB inc_files  "./inc/*.h")
source_group("inc" FILES ${inc_files})

file(GLOB src_files  "./src/*.cpp" )
source_group("src" FILES ${src_files})

#Set include directories
include_directories(
    inc
	${cc_tools_root}/ConcurrencePath/inc
)

add_executable( ${PROJECT_NAME}
	${inc_files}
	${src_files}
)

target_link_libraries(${PROJECT_NAME}
	ConcurrencePath.lib
)

# if(${use_software_environment} STREQUAL "iFLYEK")

#     file(GLOB openssl_dll_files  ${openssl_dll_dir}/*.dll)
    
#     add_custom_command(
#         TARGET ${PROJECT_NAME}
#         POST_BUILD
#         # curl dll
#         COMMAND ${CMAKE_COMMAND} -E copy_directory ${curl_dll_dir} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # jsoncpp dll
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different ${jsoncpp_dll_dir}/jsoncpp.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # openssl dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${openssl_dll_files} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}	
#         # boost random dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${boost_lib_dir}/${boost_random_lib_name}.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # boost system dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${boost_lib_dir}/${boost_system_lib_name}.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#     )	
    
# else()
#     file(GLOB opencv_dll_files  ${opencv_dll_dir}/*.dll)
#     file(GLOB openssl_dll_files  ${openssl_dll_dir}/*.dll)
#     file(GLOB vosk_dll_files  ${vosk_lib_dir}/*.dll)

#     add_custom_command(
#         TARGET ${PROJECT_NAME} 
#         POST_BUILD
#         # opencv dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${opencv_dll_files} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # tensorflow dll		
#         COMMAND ${CMAKE_COMMAND} -E copy ${tensorflow_lib_dir}/tensorflowlite_c.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # curl dll
#         COMMAND ${CMAKE_COMMAND} -E copy_directory ${curl_dll_dir} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # jsoncpp dll
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different ${jsoncpp_dll_dir}/jsoncpp.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # openssl dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${openssl_dll_files} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}		
#         # vosk dll
#         COMMAND ${CMAKE_COMMAND} -E copy ${vosk_dll_files} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # onnxruntime dll
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different ${onnxruntime_lib_dir}/onnxruntime.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # rabbitmq dll	
#         # COMMAND ${CMAKE_COMMAND} -E copy_if_different ${rabbitmq_dll_dir}/rabbitmq.4.dll ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#         # extra dll	
#         COMMAND ${CMAKE_COMMAND} -E copy_directory ${zw_resource_dir}/ExtraDlls/${ZW_PLATFORM} ${zw_exe_dir}/${CMAKE_BUILD_TYPE}
#     )
# endif()
    
    
set_target_properties( ${PROJECT_NAME}
	PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${cc_exe_dir}
  )
  
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "ConcurrenceModule")
 
 