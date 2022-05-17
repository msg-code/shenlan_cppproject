CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)
 
#项目名称
PROJECT(project5)
 
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
 
# 根目录/代码路径
aux_source_directory(. DIR_MAIN)
 
#dubug 模式-----------------------it's very import for Debug
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
# 编译成可执行文件
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)       ###### 输出可执行文件目录
add_executable(main ${DIR_MAIN})
# 链接rdlib库，注意下面子目录src的CMakeLists
# link_directories("${PROJECT_SOURCE_DIR}/lib")
# target_link_libraries(main rdlib)
