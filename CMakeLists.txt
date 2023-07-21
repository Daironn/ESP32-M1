cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(EXTRA_COMPONENT_DIRS drivers/Hardware main)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(ESP32-M1)

# find_package(libmongocxx REQUIRED)
# find_package(libbsoncxx REQUIRED)
# include_directories(${LIBMONGOCXX_INCLUDE_DIR})
# include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/lib")

# add_executable(ESP32 ${SOURCE_FILES})

# target_link_libraries(ESP32 ${LIBMONGOCXX_LIBRARIES})
# target_link_libraries(ESP32 ${LIBBSONCXX_LIBRARIES})