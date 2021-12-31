cmake_minimum_required(VERSION 3.18)

project(protobuf_to_geojson)

option(USE_PBF_WORKAROUND "Use workaround to generate geojson from protobuf" OFF)

# Build nlohmann_json
include(nlohmann_json.cmake)
# Build protobuf
include(protobuf.cmake)

# Generate protobuf sources
add_subdirectory(proto)

# Build target
add_subdirectory(src)
add_subdirectory(create_protobuf)
add_subdirectory(pbf_to_geojson)