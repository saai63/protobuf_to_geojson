# ==================================================================================================
# protobuf_to_geojson
# ==================================================================================================

cmake_minimum_required(VERSION 3.18)

project(protobuf_to_geojson)

add_executable(protobuf_to_geojson main.cpp)
target_link_libraries(protobuf_to_geojson proto protobuf nlohmann_json)