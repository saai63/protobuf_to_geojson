# ==================================================================================================
# visualizationInterface
# ==================================================================================================

cmake_minimum_required(VERSION 3.18)

project(visualization_interface)

# Library
add_library(visualization_interface STATIC protobufVisualizer.h protobufVisualizer.cpp)
set_property(TARGET visualization_interface PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(visualization_interface PRIVATE nlohmann_json proto)
target_include_directories(visualization_interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set_target_properties(visualization_interface PROPERTIES PUBLIC_HEADER IVisualization.h visualization_types.h protobufVisualizer.h)