# Build protobuf as as an external project

include(ExternalProject)
set(PROTOBUF_INSTALL_DIR "${CMAKE_BINARY_DIR}/install")
set(PROTOBUF_LIB_DEBUG "${PROTOBUF_INSTALL_DIR}/lib/libprotobufd.a")
set(PROTOBUF_LIB_RELEASE "${PROTOBUF_INSTALL_DIR}/lib/libprotobuf.a")
set(PROTOBUF_LIB_RELWITHDEBINFO "${PROTOBUF_INSTALL_DIR}/lib/libprotobuf.a")
set(PROTOBUF_PROTOC_EXECUTABLE "${PROTOBUF_INSTALL_DIR}/bin/protoc" CACHE STRING "Protoc binary on host")
set(PROTOBUF_BASE_INCLUDE_DIR "${PROTOBUF_INSTALL_DIR}/include" CACHE STRING "Protobuf base include directory")
set(PROTOBUF_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -DGOOGLE_PROTOBUF_NO_RTTI")

ExternalProject_Add(
		protobuf_external
		PREFIX protobuf
		SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/protobuf/cmake"
		CMAKE_ARGS
		-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
		-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_CXX_FLAGS=${PROTOBUF_CXX_FLAGS}
		-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}
		-DCMAKE_INSTALL_PREFIX:PATH=${PROTOBUF_INSTALL_DIR}
		-DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=ON
		CMAKE_CACHE_ARGS
		-Dprotobuf_BUILD_TESTS:BOOL=OFF)
# ==================================================================================================
# protobuf
# ==================================================================================================

add_library(
        protobuf
        STATIC
        IMPORTED
        GLOBAL)

file(MAKE_DIRECTORY ${PROTOBUF_BASE_INCLUDE_DIR})
add_dependencies(protobuf protobuf_external)

set_target_properties(
        protobuf
        PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${PROTOBUF_BASE_INCLUDE_DIR}
        IMPORTED_LOCATION_DEBUG ${PROTOBUF_LIB_DEBUG}
        IMPORTED_LOCATION_RELEASE ${PROTOBUF_LIB_RELEASE}
        IMPORTED_LOCATION_RELWITHDEBINFO ${PROTOBUF_LIB_RELWITHDEBINFO}
        #COMPILE_FLAGS ${disable_warnings_option}
        INTERFACE_COMPILE_OPTIONS -DGOOGLE_PROTOBUF_NO_RTTI)

# ==================================================================================================
# protobuf_generate_cpp
# ==================================================================================================

function(protobuf_generate_cpp SRC_FILES HDR_FILES PROTOBUF_INCLUDE_PATH PROTOBUF_GEN_CPP_DIR PROTOBUF_GEN_PYTHON_RELPATH)
    if(NOT ARGN)
        message(SEND_ERROR "Calling protobuf_generate_cpp() without any proto files!")
        return()
    endif()

    set(${SRC_FILES})
    set(${HDR_FILES})
    file(MAKE_DIRECTORY ${PROTOBUF_GEN_CPP_DIR})

    foreach(FIL ${ARGN})
        message(STATUS "Calling protobuf_generate_cpp with file " ${FIL})

        get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
        get_filename_component(FIL_WE ${FIL} NAME_WE)

        list(APPEND ${SRC_FILES} "${PROTOBUF_GEN_CPP_DIR}/${FIL_WE}.pb.cc")
        list(APPEND ${HDR_FILES} "${PROTOBUF_GEN_CPP_DIR}/${FIL_WE}.pb.h")

        add_custom_command(
                OUTPUT "${PROTOBUF_GEN_CPP_DIR}/${FIL_WE}.pb.cc"
                "${PROTOBUF_GEN_CPP_DIR}/${FIL_WE}.pb.h"
                COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
                ARGS --cpp_out=${PROTOBUF_GEN_CPP_DIR}
                -I ${PROTOBUF_BASE_INCLUDE_DIR}
                -I ${PROTOBUF_INCLUDE_PATH}
                ${ABS_FIL}
                WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                DEPENDS ${ABS_FIL} )

    endforeach()

    set_source_files_properties(${${SRC_FILES}} ${${HDR_FILES}} PROPERTIES GENERATED TRUE)
    set(${SRC_FILES} ${${SRC_FILES}} PARENT_SCOPE)
    set(${HDR_FILES} ${${HDR_FILES}} PARENT_SCOPE)
endfunction()
