cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(window_standalone LANGUAGES CXX)

# --- Import tools ----
include(../cmake/tools.cmake)

# ---- Dependencies ----
include(../cmake/CPM.cmake)

CPMAddPackage(NAME window SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# ---- Create standalone executable ----
file(GLOB sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

add_executable(${PROJECT_NAME} ${sources})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 20
    OUTPUT_NAME "window"
)

target_link_libraries(${PROJECT_NAME} window)

# This line will create a folder hierarchy in the Visual Studio solution explorer
# that matches the directory structure under ${CMAKE_CURRENT_SOURCE_DIR}/source.
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/source" FILES ${sources})

# ---- Copy data folder ----
set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data")
set(DEST_DIR "${CMAKE_BINARY_DIR}/runtime/data")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${DATA_DIR}" "${DEST_DIR}"
    COMMENT "Copying data folder to build directory"
)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/runtime")
