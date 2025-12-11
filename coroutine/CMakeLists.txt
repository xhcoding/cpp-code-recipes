enable_language(ASM)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -z noexecstack")

add_executable(stackful_co coroutine.c main.c coroutine_swap.S)

add_executable(stackless_co stackless_co.c)


add_subdirectory(cpp20)
