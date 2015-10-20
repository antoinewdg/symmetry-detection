cmake_minimum_required(VERSION 2.8)
project(symmetry_detection)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wreturn-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/test/test_util")
file(GLOB_RECURSE source_files src/*.cpp)
list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB_RECURSE header_files include/*.h)
add_executable(main src/main.cpp ${source_files} ${header_files})



# TESTING =====================

enable_testing()
find_package(GTest)

if (GTEST_FOUND)
    file(GLOB_RECURSE test_files test/*.cpp test/*.h)
    add_executable(testing ${source_files} ${header_files} ${test_files})
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(testing ${GTEST_LIBRARIES} pthread)
else()
    message(WARNING "Could not find GTest")
endif ()

# EXTERNAL LIBRAIRIES =====================

# OpenMesh
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(OpenMesh REQUIRED)
include_directories(${OPENMESH_INCLUDE_DIRS})
set(PROJECT_LIBS ${PROJECT_LIBS} ${OPENMESH_LIBRARIES})

# OpenCV
set(OpenCV_STATIC OFF)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(PROJECT_LIBS ${PROJECT_LIBS} ${OpenCV_LIBS})


# Linking ======
target_link_libraries(main ${PROJECT_LIBS})
if (GTEST_FOUND)
    target_link_libraries(testing ${PROJECT_LIBS})
endif ()








