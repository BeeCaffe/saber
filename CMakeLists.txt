cmake_minimum_required(VERSION 3.10)
project(saber)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o3 -g -std=c++11 -Wall -Wno-deprecated")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -o0 -ggdb -std=c++11 -Wall -Wno-deprecated")
set(CMAKE_CXX_STANDARD 14)
cmake_minimum_required(VERSION 3.10)
project(saber)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
include_directories(/usr/local/soft/yaml-cpp/include/)
link_directories(/usr/local/soft/yaml-cpp/lib/)
find_library(YAMLCPP yaml-cpp)

set(LIB_SRC
        saber/log.cc
		saber/utils.cc
		saber/json/json.cc
		saber/config.cc
		saber/thread.cc
        saber/fiber.cc
        saber/scheduler.cc
        saber/iomanager.cc
        saber/timer.cc
	)
add_library(saber SHARED ${LIB_SRC})
add_library(saber_static STATIC ${LIB_SRC})
SET_TARGET_PROPERTIES(saber_static PROPERTIES OUTPUT_NAME "saber")


set(LIB_LIB
	saber
	pthread
	${YAMLCPP}
		)

add_executable(log_test tests/log_test.cc)
add_dependencies(log_test saber)
target_link_libraries(log_test ${LIB_LIB})

add_executable(json_test tests/json_test.cc)
add_dependencies(json_test saber)
target_link_libraries(json_test ${LIB_LIB})

add_executable(config_test tests/config_test.cc)
add_dependencies(config_test saber)
target_link_libraries(config_test ${LIB_LIB})

add_executable(thread_test tests/thread_test.cc)
add_dependencies(thread_test saber)
target_link_libraries(thread_test ${LIB_LIB})

add_executable(marco_test tests/marco_test.cc)
add_dependencies(marco_test saber)
target_link_libraries(marco_test ${LIB_LIB})

add_executable(fiber_test tests/fiber_test.cc)
add_dependencies(fiber_test saber)
target_link_libraries(fiber_test ${LIB_LIB})

add_executable(scheduler_test tests/scheduler_test.cc)
add_dependencies(scheduler_test saber)
target_link_libraries(scheduler_test ${LIB_LIB})

add_executable(io_test tests/io_test.cc)
add_dependencies(io_test saber)
target_link_libraries(io_test ${LIB_LIB})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/lib)

