cmake_minimum_required(VERSION 3.26)
project(Lab01)

# C++17 编译标准
set(CMAKE_CXX_STANDARD 17)
# 设置根目录
set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# 添加头文件
include_directories(${ROOT_DIR}/include)
# 添加源文件
aux_source_directory(${ROOT_DIR}/src DIR_SRC)
aux_source_directory(${ROOT_DIR}/src/test DIR_TEST)

add_executable(Lab01
        ${DIR_SRC}
        ${DIR_TEST}
)

#include(FetchContent)
#FetchContent_Declare(
#        doctest
#        GIT_REPOSITORY https://github.com/doctest/doctest.git
#        GIT_TAG v2.4.9
#        GIT_SHALLOW TRUE
#)
#FetchContent_MakeAvailable(doctest)
#
#target_link_libraries(Lab01 doctest_with_main)