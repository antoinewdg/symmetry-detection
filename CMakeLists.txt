cmake_minimum_required(VERSION 2.8)
project(opencv_base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files include/*.h)
add_executable(main ${source_files} ${header_files})



# EXTERNAL LIBRAIRIES =====================

# OpenCV
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(main ${OpenCV_LIBS})


