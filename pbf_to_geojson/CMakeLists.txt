# ==================================================================================================
# protobuf_to_geojson
# ==================================================================================================

cmake_minimum_required(VERSION 3.18)

project(protobuf_to_geojson)

add_executable(protobuf_to_geojson main.cpp)
if(USE_PBF_WORKAROUND)
    message("Work around for geojson generation enabled")
    target_compile_definitions(protobuf_to_geojson PRIVATE MANUAL_JSON_CREATION)
endif()
target_link_libraries(protobuf_to_geojson proto protobuf nlohmann_json)