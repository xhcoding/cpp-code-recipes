cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(UNIX)
  execute_process(COMMAND ${CMAKE_COMMAND} -E remove "${CMAKE_SOURCE_DIR}/compile_commands.json")
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_SOURCE_DIR}/compile_commands.json"
  )
endif()

project(cpp-code-recipes)

find_package(Catch2 3 REQUIRED)

add_subdirectory(performance)
add_subdirectory(linker)
add_subdirectory(coroutine)
