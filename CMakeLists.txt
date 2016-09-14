set(PRJ_NAME "grpc_benchmark")
project(${PRJ_NAME})
cmake_minimum_required(VERSION 2.8)

# gtest package
find_package(GTest REQUIRED)

# protobuf
# FindProtobuf package in CMake was tailored to Windows environment.
# We use hard-coded path on Linux for now.
if(MSVC)
    include(FindProtobuf)
    find_package(Protobuf REQUIRED)
else()
    set(PROTOBUF_ROOT_DIR "/opt/protobuf")
    set(PROTOBUF_INCLUDE_DIR "${PROTOBUF_ROOT_DIR}/include")
    set(PROTOBUF_LIBRARY_DIR "${PROTOBUF_ROOT_DIR}/lib")
    set(PROTOBUF_PROTOC_EXECUTABLE "${PROTOBUF_ROOT_DIR}/bin/protoc")
    set(PROTOBUF_LIBRARY "protobuf")
    set(GRPC_ROOT_DIR "/opt/grpc")
    set(GRPC_LIBRARY_DIR "${GRPC_ROOT_DIR}/lib")
    set(GRPC_INCLUDE_DIR "${GRPC_ROOT_DIR}/include")
    set(GRPC_CPP_PLUGIN "grpc_cpp_plugin")
    set(GRPC_LIBRARY "grpc++ grpc")
endif()

set(PROTO_PATH "${CMAKE_SOURCE_DIR}/protos")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})
### control.proto
set(control_file_suffix "control")
set(control_proto_file "${PROTO_PATH}/${control_file_suffix}.proto")

set(control_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${control_file_suffix}.pb.cc")
set(control_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${control_file_suffix}.pb.h")
set(control_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${control_file_suffix}.grpc.pb.cc")
set(control_grpc_pb_h_file   "${GENERATED_PROTOBUF_PATH}/${control_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${control_pb_h_file}"
            "${control_pb_cpp_file}"
            "${control_grpc_pb_h_file}"
            "${control_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${control_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${control_proto_file}"
    )
### stats.proto
set(stats_file_suffix "stats")
set(stats_proto_file "${PROTO_PATH}/${stats_file_suffix}.proto")

set(stats_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${stats_file_suffix}.pb.cc")
set(stats_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${stats_file_suffix}.pb.h")
set(stats_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${stats_file_suffix}.grpc.pb.cc")
set(stats_grpc_pb_h_file   "${GENERATED_PROTOBUF_PATH}/${stats_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${stats_pb_h_file}"
            "${stats_pb_cpp_file}"
            "${stats_grpc_pb_h_file}"
            "${stats_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${stats_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${stats_proto_file}"
    )
### messages.proto
set(messages_file_suffix "messages")
set(messages_proto_file "${PROTO_PATH}/${messages_file_suffix}.proto")

set(messages_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${messages_file_suffix}.pb.cc")
set(messages_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${messages_file_suffix}.pb.h")
set(messages_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${messages_file_suffix}.grpc.pb.cc")
set(messages_grpc_pb_h_file   "${GENERATED_PROTOBUF_PATH}/${messages_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${messages_pb_h_file}"
            "${messages_pb_cpp_file}"
            "${messages_grpc_pb_h_file}"
            "${messages_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${messages_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${messages_proto_file}"
    )
### payloads.proto
set(payloads_file_suffix "payloads")
set(payloads_proto_file "${PROTO_PATH}/${payloads_file_suffix}.proto")

set(payloads_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${payloads_file_suffix}.pb.cc")
set(payloads_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${payloads_file_suffix}.pb.h")
set(payloads_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${payloads_file_suffix}.grpc.pb.cc")
set(payloads_grpc_pb_h_file   "${GENERATED_PROTOBUF_PATH}/${payloads_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${payloads_pb_h_file}"
            "${payloads_pb_cpp_file}"
            "${payloads_grpc_pb_h_file}"
            "${payloads_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${payloads_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${payloads_proto_file}"
    )
### services.proto
set(services_file_suffix "services")
set(services_proto_file "${PROTO_PATH}/${services_file_suffix}.proto")

set(services_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${services_file_suffix}.pb.cc")
set(services_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${services_file_suffix}.pb.h")
set(services_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${services_file_suffix}.grpc.pb.cc")
set(services_grpc_pb_h_file    "${GENERATED_PROTOBUF_PATH}/${services_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${services_pb_h_file}"
            "${services_pb_cpp_file}"
            "${services_grpc_pb_h_file}"
            "${services_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${services_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${services_proto_file}"
    )
### datastream.proto
set(datastream_file_suffix "datastream")
set(datastream_proto_file "${PROTO_PATH}/${datastream_file_suffix}.proto")

set(datastream_pb_cpp_file      "${GENERATED_PROTOBUF_PATH}/${datastream_file_suffix}.pb.cc")
set(datastream_pb_h_file        "${GENERATED_PROTOBUF_PATH}/${datastream_file_suffix}.pb.h")
set(datastream_grpc_pb_cpp_file "${GENERATED_PROTOBUF_PATH}/${datastream_file_suffix}.grpc.pb.cc")
set(datastream_grpc_pb_h_file   "${GENERATED_PROTOBUF_PATH}/${datastream_file_suffix}.grpc.pb.h")
add_custom_command(
    OUTPUT  "${datastream_pb_h_file}"
            "${datastream_pb_cpp_file}"
            "${datastream_grpc_pb_h_file}"
            "${datastream_grpc_pb_cpp_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--cpp_out=${GENERATED_PROTOBUF_PATH}"
            "${datastream_proto_file}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS    "--proto_path=${PROTO_PATH}"
            "--grpc_out=${GENERATED_PROTOBUF_PATH}"
            "--plugin=protoc-gen-grpc=${GRPC_ROOT_DIR}/bin/${GRPC_CPP_PLUGIN}"
            "${datastream_proto_file}"
    )
###
set(GENERATED_PROTOBUF_FILES
    ${control_pb_cpp_file}
    ${control_grpc_pb_cpp_file}
    ${stats_pb_cpp_file}
    ${stats_grpc_pb_cpp_file}
    ${messages_pb_cpp_file}
    ${messages_grpc_pb_cpp_file}
    ${payloads_pb_cpp_file}
    ${payloads_grpc_pb_cpp_file}
    ${services_pb_cpp_file}
    ${services_grpc_pb_cpp_file}
    ${datastream_pb_cpp_file}
    ${datastream_grpc_pb_cpp_file}
    )
include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

# indexlet
find_package (Threads)

set(CXX_OPT_FLAGS "-O3 -ffast-math -funroll-loops -msse4.2")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_OPT_FLAGS}")

find_package(Boost 1.42.0 COMPONENTS iostreams filesystem system program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIR})

set(GRPC_BENCHMARK_HDRS
    data/ssl_test_data.h
    utils/benchmark_config.h
    utils/usage_timer.h
    utils/histogram.h
    utils/interarrival.h
    utils/limit_cores.h
    utils/parse_json.h
    utils/port_server_client.h
    utils/port.h
    utils/env.h
    utils/string.h
    utils/test_config.h
    utils/test_config_cpp.h
    utils/grpc_profiler.h
    utils/report.h
    utils/stats.h
    utils/create_test_channel.h
    qps_worker.h
    driver.h
    client.h
    server.h
    )

set(GRPC_BENCHMARK_SRC
    ${GENERATED_PROTOBUF_FILES}
    data/client_certs.c
    data/server1_cert.c
    data/server1_key.c
    data/test_root_cert.c
    utils/benchmark_config.cpp
    utils/usage_timer.cpp
    utils/limit_cores.cpp
    utils/parse_json.cpp
    utils/port_server_client.c
    utils/port_posix.c
    utils/env_posix.cpp
    utils/string.c
    utils/test_config.c
    utils/test_config_cpp.cpp
    utils/grpc_profiler.cpp
    utils/report.cpp
    utils/create_test_channel.cpp
    driver.cpp
    qps_worker.cpp
    client_sync.cpp
    client_async.cpp
    server_sync.cpp
    server_async.cpp
    )

set(GRPC_INCLUDE "/opt/grpc/include")
include_directories(
    ${DS2I_INCLUDE_PATH}
    ${USER_INCLUDE_PATH}
    ${GRPC_INCLUDE}
    ${GTEST_INCLUDE_DIRS}
)
link_directories(${Boost_LIBRARY_DIRS} ${USER_LIB_PATH} ${GRPC_LIBRARY_DIR} ${PROTOBUF_LIBRARY_DIR})

set(DEPENDENCIES_LIBRARIES
    grpc++
    grpc
    protobuf
    gflags
    gtest
    ${Boost_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    )

add_custom_target(headers SOURCES ${GRPC_BENCHMARK_HDRS})

# qps_json_driver
# add_executable(qps_json_driver qps_json_driver.cpp ${GRPC_BENCHMARK_SRC})
# target_link_libraries(qps_json_driver ${DEPENDENCIES_LIBRARIES})

# worker
# add_executable(qps_worker worker.cpp ${GRPC_BENCHMARK_SRC})
# target_link_libraries(qps_worker ${DEPENDENCIES_LIBRARIES})

# datastream client
add_executable(datastreamclient datastreamclient.cpp utils/test_config_cpp.cpp ${GENERATED_PROTOBUF_FILES})
target_link_libraries(datastreamclient ${DEPENDENCIES_LIBRARIES})

# datastream server
add_executable(datastreamserver datastreamserver.cpp ${GENERATED_PROTOBUF_FILES})
target_link_libraries(datastreamserver ${DEPENDENCIES_LIBRARIES})
