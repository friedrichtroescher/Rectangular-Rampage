cmake_minimum_required(VERSION 3.26)
project(CPP_HWR_SoSe_2025)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(CPP_HWR_SoSe_2025 main.cpp)
target_compile_features(CPP_HWR_SoSe_2025 PRIVATE cxx_std_17)
target_link_libraries(CPP_HWR_SoSe_2025 PRIVATE SFML::Graphics)