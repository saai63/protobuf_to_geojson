# Creation of protobuf
cmake_minimum_required(VERSION 3.18)

project(create_protobuf)
add_executable(create_protobuf test_protobuf.cpp)
target_link_libraries(create_protobuf PRIVATE visualization_interface nlohmann_json proto)
