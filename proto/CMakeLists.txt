# ==================================================================================================
# proto
# ==================================================================================================

set(proto_gen_dir "${CMAKE_CURRENT_SOURCE_DIR}/srcgen")
set(proto_root
        ${CMAKE_CURRENT_LIST_DIR})
set(proto_schemas
        ${proto_root}/visualization.proto)
protobuf_generate_cpp(
        proto_gen_source
        proto_gen_header
        ${proto_root}
        ${proto_gen_dir}
        "protobuf_to_geojson"
        ${proto_schemas} )

add_library(
        proto
        STATIC
        ${proto_gen_header}
        ${proto_gen_source}
        ${proto_schemas})

set_target_properties(proto PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(
        proto
        PUBLIC
        ${proto_gen_dir})

target_link_libraries(
        proto
        protobuf)
