cmake_minimum_required(VERSION 3.10)
project(miniplat)


macro (add_sources)
    file (RELATIVE_PATH _relPath "${PROJECT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate SRCS to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()


add_sources(main.cpp)
add_subdirectory("game")
add_executable(miniplat ${SRCS})

FIND_PACKAGE(SDL2 REQUIRED)

find_library(SDL2_NET_LIBRARY
  NAMES SDL2_net)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(miniplat ${SDL2_LIBRARIES} ${SDL2_NET_LIBRARY})
