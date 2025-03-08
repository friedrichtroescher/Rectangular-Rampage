cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)


add_executable(main src/main.cpp
        src/Projectile.cpp
        src/include/Projectile.h
        src/Player.cpp
        src/include/Player.h
        src/Direction.cpp
        src/include/Direction.h
        src/Input.cpp
        src/include/Input.h
        src/Scoreboard.cpp
        src/include/Scoreboard.h
        src/Combatant.cpp
        src/include/Combatant.h
        src/Direction.cpp
        src/include/Direction.h
        src/GameLoop.cpp
        src/include/GameLoop.h
        src/Monster.cpp
        src/include/Monster.h
        src/Game.cpp
        src/include/Game.h
        src/Random.cpp
        src/include/Random.h
)

set(FONT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/resources/fonts")

file(COPY ${FONT_DIR}/Press_Start_2P/PressStart2P-Regular.ttf
        DESTINATION ${CMAKE_BINARY_DIR}/bin/fonts)


target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
