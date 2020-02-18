cmake_minimum_required(VERSION 3.10)
project(saber)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o3 -g -std=c++11 -Wall -Wno-deprecated")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o0 -ggdb -std=c++11 -Wall -Wno-deprecated")
set(CMAKE_CXX_STANDARD 14)
cmake_minimum_required(VERSION 3.10)
project(saber)

set(CMAKE_CXX_STANDARD 14)

set(LIB_SRC
        saber/log.cc
		saber/utils.cc
		saber/json/json.cc
	)
add_library(saber SHARED ${LIB_SRC})
add_library(saber_static STATIC ${LIB_SRC})
SET_TARGET_PROPERTIES(saber_static PROPERTIES OUTPUT_NAME "saber")
add_executable(log_test tests/log_test.cc)
add_dependencies(log_test saber)
target_link_libraries(log_test saber)

add_executable(json_test tests/json_test.cc)
add_dependencies(json_test saber)
target_link_libraries(json_test saber)

add_executable(jsoncc_test tests/jsoncc_test.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib)

