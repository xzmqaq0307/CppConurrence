cmake_minimum_required(VERSION 3.9)

set(cc_tools_root ${CMAKE_CURRENT_SOURCE_DIR}/ConcurrenceTools)
set(cc_chapter_root ${CMAKE_CURRENT_SOURCE_DIR}/ConcurrenceChapter)

# set(zw_aimodule_api_root ${CMAKE_CURRENT_SOURCE_DIR}/ZwAiModuleApi)
# set(zw_aimodule_manager_root ${CMAKE_CURRENT_SOURCE_DIR}/ZwAiModuleManager)
# set(zw_thread_root ${CMAKE_CURRENT_SOURCE_DIR}/ZwAiThread)
# add_subdirectory(ZwAiModuleApi)
# add_subdirectory(ZwAiModuleManager)
# if(${ZW_PLATFORM} STREQUAL "x64")
#     add_subdirectory(ZwAiThread)
# endif()

add_subdirectory(ConcurrenceModule)
add_subdirectory(ConcurrenceTools)
add_subdirectory(ConcurrenceChapter)

