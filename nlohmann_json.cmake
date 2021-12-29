# ==================================================================================================
# nlohmann_json_external
# ==================================================================================================

set(NLOHMANN_JSON_INSTALL_DIR ${CMAKE_BINARY_DIR}/install)
set(NLOHMANN_JSON_INCLUDE_DIR ${NLOHMANN_JSON_INSTALL_DIR}/include)

file(MAKE_DIRECTORY ${NLOHMANN_JSON_INCLUDE_DIR})
include(ExternalProject)

ExternalProject_Add(
        nlohmann_json_external
        PREFIX nlohmann_json
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/json/"
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${NLOHMANN_JSON_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX:PATH=${NLOHMANN_JSON_INSTALL_DIR}
        -DJSON_ImplicitConversions:BOOL=OFF
        -DJSON_BuildTests=OFF
        BUILD_IN_SOURCE 0)

# ==================================================================================================
# nlohmann_json
# ==================================================================================================

add_library(
        nlohmann_json
        INTERFACE
        IMPORTED
        GLOBAL)

add_dependencies(nlohmann_json nlohmann_json_external)

set_target_properties(
        nlohmann_json
        PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${NLOHMANN_JSON_INCLUDE_DIR})