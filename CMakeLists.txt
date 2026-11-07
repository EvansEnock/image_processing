cmake_minimum_required(VERSION 3.20)
project(image_processing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(stb)

add_library(image_processing_core
    src/image.cpp src/operations.cpp src/io.cpp src/cli.cpp)
target_include_directories(image_processing_core PUBLIC include PRIVATE ${stb_SOURCE_DIR})
if(MSVC)
    target_compile_options(image_processing_core PRIVATE /W4)
else()
    target_compile_options(image_processing_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(image_processing src/main.cpp)
target_link_libraries(image_processing PRIVATE image_processing_core)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
