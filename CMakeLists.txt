cmake_minimum_required(VERSION 3.16)
project(PhysicsEngine VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Main build
file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")
add_library(physics_objects OBJECT ${SOURCES})
set_target_properties(physics_objects PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_library(physics_static STATIC $<TARGET_OBJECTS:physics_objects>)
set_target_properties(physics_static PROPERTIES OUTPUT_NAME "physics")
add_library(physics_shared SHARED $<TARGET_OBJECTS:physics_objects>)
set_target_properties(physics_shared PROPERTIES OUTPUT_NAME "physics")

# Examples
add_library(examples_common OBJECT EXCLUDE_FROM_ALL examples/common/main.cpp)
set_target_properties(examples_common PROPERTIES POSITION_INDEPENDENT_CODE ON)

set(EXAMPLE_TARGETS "")

file(GLOB EXAMPLE_SOURCES "examples/*.cpp")
foreach(example_src ${EXAMPLE_SOURCES}) 
    get_filename_component(example_name ${example_src} NAME_WE)
    add_executable(${example_name} EXCLUDE_FROM_ALL ${example_src} $<TARGET_OBJECTS:examples_common>)
    target_link_libraries(${example_name} PRIVATE physics_static sfml-graphics sfml-window sfml-system)

    list(APPEND EXAMPLE_TARGETS ${example_name})
endforeach()

add_custom_target(examples
    DEPENDS ${EXAMPLE_TARGETS}
    COMMENT "Build all examples"
)
